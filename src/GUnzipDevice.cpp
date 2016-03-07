/*
 * GUnzipDevice.cpp
 *
 *  Created on: 01.04.2011
 *      Author: iface
 */

#include "GUnzipDevice.h"
#include <errno.h>
#include <zlib.h>

namespace qtGunzip
{
	struct GZIPStream
	{
			const static int Z_BUFSIZE = 16384;
			const static int DEF_MEM_LEVEL = 8;

			const static int OS_CODE = 0x03;

			const static int ASCII_FLAG = 0x01;
			const static int HEAD_CRC = 0x02;
			const static int EXTRA_FIELD = 0x04;
			const static int ORIG_NAME = 0x08;
			const static int COMMENT = 0x10;
			const static int RESERVED = 0xE0;

			z_stream zStream;

			int z_err;
			int z_eof;

			QIODevice * device;

			unsigned char inbuf [Z_BUFSIZE];

			unsigned long crc;
			int transparent;
			char mode;
			long startpos;

			GZIPStream(QIODevice * device);

			int destroy();
			unsigned long getLong();
			int get_byte();
			void check_header();
			int gzClose();

			int gzRead(void * buf, unsigned len);

			static GZIPStream * openGZFile(QIODevice * device);

	};


	//-------------------------------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------------------------------------------------
	static int gz_magic [2] =
	{ 0x1f, 0x8b };

	GZIPStream::GZIPStream(QIODevice * ins)
	{
		z_err = 0;
		z_eof = 0;
		device = ins;
		crc = 0;
		transparent = 0;
		mode = 0;
		startpos = 0;

		zStream.zalloc = (alloc_func) 0;
		zStream.zfree = (free_func) 0;
		zStream.opaque = (voidpf) 0;
		zStream.next_in = NULL;
		zStream.next_out = NULL;
		zStream.avail_in = zStream.avail_out = 0;

	}


	//---------------------------------------------------------------------------------------
	int GZIPStream::destroy()
	{
		int err = Z_OK;

		if (zStream.state != NULL)
		{
			err = inflateEnd(&(zStream));
		}

		if (z_err < 0)
			err = z_err;

		return err;
	}


	//---------------------------------------------------------------------------------------
	int GZIPStream::get_byte()
	{
		//		qDebug("GZIPStream::get_byte, zStream.avail_in:%d", zStream.avail_in);

		if (z_eof)
			return EOF;

		if (zStream.avail_in == 0)
		{
			errno = 0;

			int r = device->read((char*) inbuf, Z_BUFSIZE);

			zStream.avail_in = r;

			if (r == -1)
			{
				qDebug("--------------- EOF -1 -----------------------");
				z_eof = 1;
				return EOF;
			}

			if (zStream.avail_in == 0)
			{
				if (device->atEnd())
				{
					qDebug("--------------- EOF -----------------------");
					z_err = Z_ERRNO;
					z_eof = 1;
					return EOF;
				}

			}

			zStream.next_in = inbuf;
		}
		zStream.avail_in--;

		return *(zStream.next_in)++;
	}


	//---------------------------------------------------------------------------------------
	unsigned long GZIPStream::getLong()
	{
		unsigned long x = (unsigned long) get_byte();
		int c;

		x += ((unsigned long) get_byte()) << 8;
		x += ((unsigned long) get_byte()) << 16;
		c = get_byte();

		if (c == EOF)
		{
			z_err = Z_DATA_ERROR;
		}

		x += ((unsigned long) c) << 24;

		return x;
	}


	// --------------------------------------

	void GZIPStream::check_header()
	{
		int method;
		int flags;
		uInt len;
		int c;

		for (len = 0; len < 2; len++)
		{
			c = get_byte();
			if (c != gz_magic [len])
			{
				if (len != 0)
					zStream.avail_in++, zStream.next_in--;
				if (c != EOF)
				{
					zStream.avail_in++, zStream.next_in--;
					transparent = 1;
				}
				z_err = zStream.avail_in != 0 ? Z_OK : Z_STREAM_END;
				return;
			}
		}
		method = get_byte();
		flags = get_byte();
		if (method != Z_DEFLATED || (flags & RESERVED) != 0)
		{
			z_err = Z_DATA_ERROR;
			return;
		}

		for (len = 0; len < 6; len++)
		{
			get_byte();
		}

		if ((flags & EXTRA_FIELD) != 0)
		{
			len = (uInt) get_byte();

			len += ((uInt) get_byte()) << 8;

			while (len-- != 0 && get_byte() != EOF)
				;
		}
		if ((flags & ORIG_NAME) != 0)
		{
			while ((c = get_byte()) != 0 && c != EOF)
				;
		}
		if ((flags & COMMENT) != 0)
		{
			while ((c = get_byte()) != 0 && c != EOF)
				;
		}
		if ((flags & HEAD_CRC) != 0)
		{
			for (len = 0; len < 2; len++)
				(void) get_byte();
		}
		z_err = z_eof ? Z_DATA_ERROR : Z_OK;

	}
	//---------------------------------------------------------------------------------------
	int GZIPStream::gzClose()
	{
		GZIPStream *s = this;

		if (!s)
			return Z_STREAM_ERROR;

		return s->destroy();
	}


	//-----------------------------------------------------------------------------------------------------------
	int GZIPStream::gzRead(void * buf, unsigned len)
	{

		Bytef *start = (Bytef*) buf;
		unsigned char *next_out;

		if (mode != 'r')
			return Z_STREAM_ERROR;

		if (z_err == Z_DATA_ERROR || z_err == Z_ERRNO)
			return -1;

		if (z_err == Z_STREAM_END)
			return 0;

		next_out = (unsigned char*) buf;
		zStream.next_out = (Bytef*) buf;
		zStream.avail_out = len;

		while (zStream.avail_out != 0)
		{
			if (transparent)
			{
				uInt n = zStream.avail_in;

				if (n > zStream.avail_out)
					n = zStream.avail_out;

				if (n > 0)
				{
					memcpy(zStream.next_out, zStream.next_in, n);

					next_out += n;
					zStream.next_out = next_out;
					zStream.next_in += n;
					zStream.avail_out -= n;
					zStream.avail_in -= n;
				}

				if (zStream.avail_out > 0)
				{
					zStream.avail_out -= device->read((char*) next_out, zStream.avail_out);
				}

				len -= zStream.avail_out;
				zStream.total_in += (unsigned long) len;
				zStream.total_out += (unsigned long) len;

				if (len == 0)
					z_eof = 1;

				return (int) len;
			}

			if (zStream.avail_in == 0 && !z_eof)
			{
				errno = 0;

				zStream.avail_in = device->read((char*) inbuf, Z_BUFSIZE);

				if (zStream.avail_in == 0)
				{
					z_eof = 1;

					z_err = Z_ERRNO;
					break;
				}
				zStream.next_in = inbuf;
			}
			z_err = inflate(&(zStream), Z_NO_FLUSH);

			if (z_err == Z_STREAM_END)
			{

				crc = crc32(crc, start, (uInt) (zStream.next_out - start));

				start = zStream.next_out;

				if (getLong() != crc)
				{
					z_err = Z_DATA_ERROR;
				}
				else
				{
					getLong();
				}
			}
			if (z_err != Z_OK || z_eof)
				break;
		}
		crc = crc32(crc, start, (uInt) (zStream.next_out - start));

		return (int) (len - zStream.avail_out);

	}


	//---------------------------------------------------------------------------------------
	GZIPStream * GZIPStream::openGZFile(QIODevice * device)
	{
		const char * mode = "rb";
		int level = Z_DEFAULT_COMPRESSION;
		int strategy = Z_DEFAULT_STRATEGY;
		char *p = (char*) mode;
		char fmode [80];
		char *m = fmode;

		if (!mode)
			return Z_NULL;

		GZIPStream *s = new GZIPStream(device);

		s->mode = '\0';
		do
		{
			if (*p == 'r')
				s->mode = 'r';

			if (*p >= '0' && *p <= '9')
			{
				level = *p - '0';
			}
			else if (*p == 'f')
			{
				strategy = Z_FILTERED;
			}
			else if (*p == 'h')
			{
				strategy = Z_HUFFMAN_ONLY;
			}
			else
			{
				*m++ = *p; /* copy the mode */
			}
		}
		while (*p++ && m != fmode + sizeof(fmode));

		if (s->mode == '\0')
		{
			s->destroy();
			return NULL;
		}

		s->zStream.next_in = s->inbuf;

		int err = inflateInit2(&(s->zStream), -MAX_WBITS);

		if (err != Z_OK)
		{
			s->destroy();
			return NULL;
		}

		s->zStream.avail_out = Z_BUFSIZE;

		errno = 0;

		s->check_header();

		s->startpos = 26; // very dirty !! - it seems ok...

		return s;
	}


	//-------------------------------------------------------------------------------------------------------------

	int GUnzipDevice::getBytes(const char *pFile, QByteArray & ar)
	{
		if (!pFile)
		{
			qDebug("GUnzipDevice::getBytes, pFile  == NULL !");
			return -1;
		}

		qDebug("GUnzipDevice::getBytes, pFile '%s'", pFile);

		QFile f(pFile);
		f.open(QIODevice::ReadOnly);

		return getBytes(&f, ar);
	}

	int GUnzipDevice::getBytes(QIODevice * ioDevice, QByteArray & ar)
	{
		if (!ioDevice)
		{
			qDebug("GUnzipDevice::getBytes, ioDevice  == NULL !");
			return -1;
		}
		GZIPStream * stream = GZIPStream::openGZFile(ioDevice);

		if (!stream)
		{
			qDebug("GUnzipDevice::getBytes, stream  == NULL !");
			return -1;
		}

		const int GZ_BUF_SIZE = 1024;
		char buf [GZ_BUF_SIZE];

		int r = stream->gzRead(buf, GZ_BUF_SIZE);
		int total = r;

		while (r > 0)
		{
			ar.append(buf, r);

			r = stream->gzRead(buf, GZ_BUF_SIZE);
			if (r > 0)
				total += r;
		}

		return total;
	}

}

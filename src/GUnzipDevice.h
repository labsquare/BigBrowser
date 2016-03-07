/*
 * GUnzipDevice.h
 *
 *  Created on: 01.04.2011
 *      Author: iface
 */

#ifndef GUnzipDevice_H_
#define GUnzipDevice_H_

#include <QtCore>

namespace qtGunzip
{
	struct GUnzipDevice
	{
			// return -1 if error occurs
			static int getBytes(QIODevice * ioDevice, QByteArray & ar);
			static int getBytes(const char *pFile, QByteArray & ar);
	};

}


#endif

// ======================================================================
//
//                    CORE MODULE
//
// =======================================================================
class Region
{
  Region(const QString& chromosom, quint64 start, quint64 end);
  Region(const QString& pattern);


  QString chromosom() const;
  void    setChromosom(const QString& chromosom);
  int     start() const;
  void    setStart(quint64 start);
  int     end() const ;
  void    setEnd(quint64 end);
  int     data(const QString& key);
  void    setData(const QString& key, const QVariant& value);
  void    clearData();
  void    translate(quint64 count);
  void    scale(quint64 count);
  int     length() const;
  int     middle() const ;
  bool    isNull() const ;
  QString toString() const;
};
  

class Genom
{
    void                load(QIODevice * device);
    void                load(const QString& filename);
    int                 chromosomCount() const;
    int                 chromosomLength(const QString& chromosom);
    QStringList         chromosoms() const;
    const QList<Region> chromosomBand(const QString& chromosom) const;
    Sequence            sequence(const Region& region);
    bool                hasCytoband() const;
};

class Sequence
{
    enum Type {
      Dna,
      Rna,
      Protein
    };

    enum Strand {
      Forward
      Reverse
    };

    Sequence(const char *data);
    Sequence(const QByteArray& bytes);
    Sequence();
    Sequence          complement() const;
    Sequence          translate()  const;
    Sequence          transcribe() const;
    Sequence          reverse()    const;
    QString           name() const;
    void              setName(const QString &name);
    Strand            strand() const;
    void              setStrand(const Strand &strand);
    Type              type() const;
    void              setType(const Type &type);
    QString           typeName();
    int               count() const;
    void              setByteArray(const QByteArray& array);
    const QByteArray& byteArray() const;
    QString           toString() const;
};

// ======================================================================
//
//                    GUI MODULE
//
// =======================================================================
class MainWindow
{
void setSelection(const Region& region);  
   

};




class SelectionRouter
{
  void addObject(QObject * obj);
  void setSelection(const Region& region);
} ;
class ChromosomViewer
{
  void setSelection(const Region& Region);
  void selectionChanged(const Region& Region);
  void setGenom(Genom* genom);

} ;

class StatusBar : public QStatusBar
{
  void setSelection(const Region& Region);
  void selectionChanged(const Region& Region);
  
};

class SelectToolBar : public QToolBar
{
  void setSelection(const Region& Region);
  void selectionChanged(const Region& Region);   
};


class TracksWidget :public QGraphicsView
{
  void                  setSelection(const Region& region);
  void                  selectionChanged(const Region& region);
  void                  setGenom(Genom * genom);
  void                  addTrack(AbstractTrack * track);
  void                  remTrack(AbstractTrack * track);
  const Region&         selection();
  AbstractTrack *       track(int index);
  AbstractTrack *       track(QString title);
  QList<AbstractTrack*> tracks();
  quint64               pixelFrameToBase(int pixel) ;
  int                   baseToPixelFrame(quint64 base) ;
  double                baseToCoeff(quint64 base);
  double                pixelFrameToCoeff(int pixel);
  
}; 
    
class AbstractTrack
 {
    TracksWidget *  tracksWidget(); 
    const Region&   selection();
    int             height() ;
    int             width();
    void            setHeight(int h);
    int             frameHeight() ;
    int             frameWidth() ;
    bool            isTrackSelected() ;
    void            setTrackSelected(bool selected);
    bool            isResizable() ;
    void            setResizable(bool isResizable);
    void            setIndex(int slotIdx); // ?
    void            setLoading(bool loading = true, QString message);
    bool            isLoading();
    int             index();
    QRectF          boundingRect() ;
    QRectF          contentboundingRect();
    virtual void    updateSelection();
    virtual void    paintFrame(QPainter * painter);
} ;

class AbstractAsyncTrack : public AbstractTrack
{


    virtual void updateSelection()
    {
        // start Thread , create QPixmap
        setLoading(true, "loading")
    }
   
    virtual QPixmap createFrame() // Virtual pure 
    {
        // create QPixmap according selection 
    }

    virtual void frameCreated()
    {
      // Frame has been created
      setLoading(false)
    }

    virtual void paintFrame(QPainter * painter)
    {
       // paint the pixmap when it's done
    }

};

class HttpTrack : public AbstractTrack
{

    virtual void updateSelection()
    {
        // create network request 
    }
   
    virtual void requestReceived()
    {

        // parse http content 
        // start Thread , create QPixmap
    }

    virtual QPixmap createFrame() // Virtual pure 
    {
        // create QPixmap according selection 
    }

    virtual void paintFrame(QPainter * painter)
    {
       // paint the pixmap when it's done
    }



};





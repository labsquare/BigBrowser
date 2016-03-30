class Region
{
  QString chromosom();
  int start();
  int end();
  int data(const QString& key);
  void setData(const QString& key, const QVariant& value);
  int length();
  int middle();
};
  

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
  void setSelection(const Region& region);
  void selectionChanged(const Region& region);
  void setGenom(Genom * genom);
  void addTrack(AbstractTrack * track);
  void remTrack(AbstractTrack * track);
  AbstractTrack * track(int index);
  AbstractTrack * track(QString title);
  QList<AbstractTrack*> tracks();
  
  quint64 pixelFrameToBase(int pixel) ;
  int     baseToPixelFrame(quint64 base) ;
  double  baseToCoeff(quint64 base);
  double  pixelFrameToCoeff(int pixel);
  
}; 
    
class AbstractTrack:
 {
    int height() ;
    int width();
    void setHeight(int h);
    int frameHeight() ;
    int frameWidth() ;
    TracksWidget * trackList(); 
    bool isTrackSelected() ;
    void setTrackSelected(bool selected);
    bool isResizable() ;
    void setResizable(bool isResizable);
    void setIndex(int slotIdx);
    int index();

    QRectF boundingRect() ;
    QRectF contentboundingRect();
   
    virtual void updateSelection();
    virtual void paintFrame(QPainter * painter);

} ;








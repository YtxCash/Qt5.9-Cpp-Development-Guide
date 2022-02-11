#ifndef WINDOW_HH
#define WINDOW_HH

#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class Window;
}
QT_END_NAMESPACE

class Window : public QMainWindow {
  Q_OBJECT

 public:
  Window(QWidget *parent = nullptr);
  ~Window();

 private slots:
  void on_actAddGroup_triggered();

  void on_actAddImages_triggered();

  void on_treeWidget_currentItemChanged(QTreeWidgetItem *current,
                                        QTreeWidgetItem *previous);

  void on_actDeleteImage_triggered();

  void on_actScanImages_triggered();

  void on_actZoomFitH_triggered();

  void on_actZoomRealSize_triggered();

  void on_actZoomIn_triggered();

  void on_actZoomFitW_triggered();

  void on_dockWidget_visibilityChanged(bool visible);

  void on_dockWidget_topLevelChanged(bool topLevel);

  void on_actDockVisible_toggled(bool arg1);

  void on_actZoomOut_triggered();

  void on_actDockFloat_toggled(bool arg1);

 private:
  Ui::Window *ui;

  enum TreeRow { kRowTop = 1001, kRowGroup, kRowImage };
  enum TreeColumn { kColItem = 0, kColItemType = 1 };

  QLabel *lab_file_name;
  QPixmap cur_pixmap;
  float pix_ratio;

  void IniTree();

  void AddGroupItem(QTreeWidgetItem *par_item, QString dir_name);
  QString GetGroupName(const QString &full_path_name);

  void AddImageItem(QTreeWidgetItem *par_item, QString image_name);
  void DisplayImage(QTreeWidgetItem *item);
  void ChangeItemCaption(QTreeWidgetItem *item);
};
#endif  // WINDOW_HH

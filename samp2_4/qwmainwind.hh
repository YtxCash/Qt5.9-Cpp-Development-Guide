#ifndef QWMAINWIND_HH
#define QWMAINWIND_HH

#include <QFontComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QProgressBar>
#include <QSpinBox>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
namespace Ui {
class QWMainWind;
}
QT_END_NAMESPACE

class QWMainWind : public QMainWindow {
  Q_OBJECT

 public:
  QWMainWind(QWidget *parent = nullptr);
  ~QWMainWind();

 private slots:
  void on_actionFontBold_triggered(bool checked);

  void on_actionFontItalic_triggered(bool checked);

  void on_actionFontUnder_triggered(bool checked);

  void on_textEdit_copyAvailable(bool b);

  void on_textEdit_currentCharFormatChanged(const QTextCharFormat &format);

  void on_spinFontSize_valueCHanged(int i);

  void on_comboFont_currentFontChanged(const QFont &font);

 private:
  Ui::QWMainWind *ui;

  void IniUi();
  void IniSignalSlots();

  QLabel *labelStatusBar;
  QProgressBar *progressBar1;
  QSpinBox *spinFontSize;
  QFontComboBox *comboFont;
};
#endif  // QWMAINWIND_HH

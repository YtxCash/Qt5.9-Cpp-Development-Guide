#ifndef WINDOW_HH
#define WINDOW_HH

#include <QDate>
#include <QLabel>
#include <QMainWindow>

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
  void on_btnSetColHeaders_clicked();

  void on_btnIniData_clicked();

  void on_tableWidget_currentCellChanged(int currentRow, int currentColumn,
                                         int previousRow, int previousColumn);

  void on_btnInsertRow_clicked();

  void on_btnAppendRow_clicked();

  void on_btnDeleteRow_clicked();

  void on_btnAutoHeight_clicked();

  void on_btnAutoWidth_clicked();

  void on_btnTableContentsToText_clicked();

  void on_chkBoxEditable_clicked(bool checked);

  void on_chkBoxShowRowHeader_clicked(bool checked);

  void on_chkBoxShowColHeader_clicked(bool checked);

  void on_chkBoxAlternatingRowColor_clicked(bool checked);

  void on_rBtnSelCell_clicked(bool checked);

  void on_rBtnSelRow_clicked(bool checked);

 private:
  Ui::Window *ui;

  enum ColumnType { kName = 1000, kSex, kBirth, kNation, kParty, kScore };
  enum ColumnNumb {
    kNameNumb = 0,
    kSecNumb,
    kBirthNumb,
    kNationNumb,
    kPartyNumb,
    kScoreNumb
  };

  QLabel *lab_cell_index;
  QLabel *lab_cell_type;
  QLabel *lab_student_ID;

  void CreatRowItema(int row_numb, QString name, QString sex, QDate birth,
                     QString nation, bool is_party, int score);

  void IniUi();
};
#endif  // WINDOW_HH

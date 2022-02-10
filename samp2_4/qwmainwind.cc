#include "qwmainwind.hh"

#include "./ui_qwmainwind.h"
#include "moc_qwmainwind.cpp"

QWMainWind::QWMainWind(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::QWMainWind) {
  ui->setupUi(this);

  IniUi();
  IniSignalSlots();
}

QWMainWind::~QWMainWind() { delete ui; }

void QWMainWind::IniUi() {
  labelStatusBar = new QLabel;
  labelStatusBar->setText(tr("Current File"));
  ui->statusbar->addWidget(labelStatusBar);

  progressBar1 = new QProgressBar;
  progressBar1->setMaximumWidth(200);
  progressBar1->setRange(0, 500);
  progressBar1->setValue(ui->textEdit->font().pointSize());
  ui->statusbar->addWidget(progressBar1);

  spinFontSize = new QSpinBox;
  spinFontSize->setRange(10, 50);
  spinFontSize->setMinimumWidth(50);
  spinFontSize->setValue(ui->textEdit->font().pointSize());
  ui->toolBar->addWidget(new QLabel("Font Size"));
  ui->toolBar->addWidget(spinFontSize);

  ui->toolBar->addSeparator();
  ui->toolBar->addWidget(new QLabel(tr("Font")));
  comboFont = new QFontComboBox;
  comboFont->setMaximumWidth(150);
  ui->toolBar->addWidget(comboFont);
}

void QWMainWind::IniSignalSlots() {
  connect(spinFontSize, &QSpinBox::valueChanged, this,
          &QWMainWind::on_spinFontSize_valueCHanged);
  connect(comboFont, &QFontComboBox::currentFontChanged, this,
          &QWMainWind::on_comboFont_currentFontChanged);
}

void QWMainWind::on_actionFontBold_triggered(bool checked) {
  QTextCharFormat fmt = ui->textEdit->currentCharFormat();
  if (checked)
    fmt.setFontWeight(QFont::Bold);
  else
    fmt.setFontWeight(QFont::Normal);

  ui->textEdit->mergeCurrentCharFormat(fmt);
}

void QWMainWind::on_actionFontItalic_triggered(bool checked) {
  QTextCharFormat fmt = ui->textEdit->currentCharFormat();
  if (checked)
    fmt.setFontItalic(checked);
  else
    fmt.setFontItalic(0);
  ui->textEdit->mergeCurrentCharFormat(fmt);
}

void QWMainWind::on_actionFontUnder_triggered(bool checked) {
  QTextCharFormat fmt = ui->textEdit->currentCharFormat();
  if (checked)
    fmt.setFontUnderline(checked);
  else
    fmt.setFontUnderline(0);
  ui->textEdit->mergeCurrentCharFormat(fmt);
}

void QWMainWind::on_textEdit_copyAvailable(bool b) {
  ui->actionCut->setEnabled(b);
  ui->actionCopy->setEnabled(b);
  ui->actionPaste->setEnabled(b);
}

void QWMainWind::on_textEdit_currentCharFormatChanged(
    const QTextCharFormat &format) {
  QTextCharFormat fmt = ui->textEdit->currentCharFormat();
  ui->actionFontBold->setChecked(fmt.font().bold());
  ui->actionFontItalic->setChecked(fmt.fontItalic());
  ui->actionFontUnder->setChecked(fmt.fontUnderline());
  spinFontSize->setValue(fmt.fontPointSize());
  comboFont->setCurrentFont(ui->textEdit->currentFont());
}

void QWMainWind::on_spinFontSize_valueCHanged(int i) {
  QTextCharFormat fmt;
  fmt.setFontPointSize(i);
  ui->textEdit->mergeCurrentCharFormat(fmt);
  progressBar1->setValue(i);
}

void QWMainWind::on_comboFont_currentFontChanged(const QFont &font) {
  QTextCharFormat fmt;
  fmt.setFont(font);
  ui->textEdit->mergeCurrentCharFormat(fmt);
}

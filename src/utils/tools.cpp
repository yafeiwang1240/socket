#include "tools.h"

Tools::Tools()
{

}

void Tools::setComboBoxData(QComboBox *box, QStringList data) {
    box->clear();
    box->addItems(data);
}

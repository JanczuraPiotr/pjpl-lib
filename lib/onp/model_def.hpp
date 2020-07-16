/*
 * Author: Piotr Janczura <piotr@janczura.pl>
 *
 */

#ifndef MODEL_DEF_H
#define MODEL_DEF_H

#include <vector>

namespace pjpl::model {

// Wartość pochodząca z tabeli bazy danych z kolumny klucza głównego tej tabeli.
typedef int AutoId;
typedef std::vector<pjpl::model::AutoId> IdSet;


class Record {
public :
    Record() = default;
    virtual ~Record() = default;
};

class Table {
public:
    Table() {};
    virtual ~Table() = default;
protected:

};

class AutomVariableRecord;

}


#endif


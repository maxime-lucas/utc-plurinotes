#include "main.h"
#include "datetime.h"

std::ostream& operator << (std::ostream& f, const Datetime& d) {

    f << d.getYear() << "-";

    if( d.getMonth() < 10 )
        f << "0";
    f << d.getMonth() << "-";

    if( d.getDay() < 10 )
        f << "0" ;
    f << d.getDay() << " ";

    if( d.getHour() < 10 )
        f << "0" ;
    f << d.getHour() << ":";

    if( d.getMin() < 10 )
        f << "0" ;
    f << d.getMin() << ":";

    if( d.getSec() < 10 )
        f << "0" ;
    f << d.getSec();

    return f;
}
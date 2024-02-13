#include <ranking/ranking.h>

using json = nlohmann::json;


Ranking::Ranking(const std::string& ranking_string) {
    std::stringstream istrm;
    istrm << ranking_string;
    read_from(istrm);
}

std::ostream& Ranking::write_to(std::ostream &ostrm) const {
    if (j_.empty())
        ostrm << left_bracket << right_bracket;
    else
        ostrm << j_.dump();

    return ostrm;
}

std::istream& Ranking::read_from(std::istream &istrm) {
    istrm >> j_;
    // TODO: implement
    return istrm;
}

std::ostream& operator<<(std::ostream& ostrm, const Ranking& r) {
    return r.write_to(ostrm);
}

std::istream& operator>>(std::istream& istrm, Ranking& r) {
    return r.read_from(istrm);
}

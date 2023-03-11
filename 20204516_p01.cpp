#include <bits/stdc++.h>

using namespace std;

class citizen {
public:
    string code;
    string date_of_birth;
    string father_code;
    string mother_code;
    bool is_alive;
    string region_code;

    citizen() { }

    citizen(string code, string date_of_birth, string father_code, string mother_code, string is_alive, string region_code) {
        this->code = code;
        this->date_of_birth = date_of_birth;
        this->father_code = father_code;
        this->mother_code = mother_code;
        this->is_alive = is_alive == "Y";
        this->region_code = region_code;
    }
};

int most_alive_ancestor(string code, map<string, citizen>& cs) {
    citizen c = cs[code];
    int ans = c.is_alive ? 0 : -1;
    if (c.father_code != "0000000") {
        int tmp = most_alive_ancestor(c.father_code, cs);
        if (tmp >= 0)
            ans = max(1 + tmp, ans);
    }
    if (c.mother_code != "0000000") {
        int tmp = most_alive_ancestor(c.mother_code, cs);
        if (tmp >= 0)
            ans = max(1 + tmp, ans);
    }
    return ans;
}

// int try_people(string code, set<string>& tried, set<string>& rm, map<string, citizen>& cs) {
//     if (code == "0000000" || tried.count(code) || rm.count(code)) {
//         return 0;
//     }
//     citizen c = cs[code];
//     if (tried.count(c.father_code) || tried.count(c.mother_code)) {
//         return 0;
//     }
//     int maxTmp = 0;

//     tried.insert(code);
//     for (auto each : cs) {
//         rm.insert(each.second.father_code);
//         rm.insert(each.second.mother_code);
//         maxTmp = max(maxTmp, try_people(each.first, tried, rm, cs));
//         rm.erase(each.second.father_code);
//         rm.erase(each.second.mother_code);
//     }
//     tried.erase(code);
//     return 1 + maxTmp;
// }

int max_unrelated_people(map<string, citizen>& cs) {
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);

    map<string, citizen> citizens;
    map<string, int> born_at;

    string code, date_of_birth, father_code, mother_code, is_alive, region_code;
    while (true) {
        cin >> code;
        if (code == "*")
            break;

        cin >> date_of_birth >> father_code >> mother_code >> is_alive >> region_code;
        citizen c(code, date_of_birth, father_code, mother_code, is_alive, region_code);

        citizens[code] = c;
        if (born_at.count(date_of_birth))
            born_at[date_of_birth] += 1;
        else
            born_at[date_of_birth] = 1;
    }

    while (true) {
        cin >> code;
        if (code == "***")
            break;

        if (code == "NUMBER_PEOPLE") {
            cout << citizens.size() << '\n';
        } else if (code == "NUMBER_PEOPLE_BORN_AT") {
            cin >> date_of_birth;
            if (born_at.count(date_of_birth)) {
                cout << born_at[date_of_birth] << '\n';
            } else {
                cout << 0 << '\n';
            }
        } else if (code == "MOST_ALIVE_ANCESTOR") {
            cin >> code;
            int ans = max(0, most_alive_ancestor(code, citizens));
            cout << ans << '\n';
        } else if (code == "NUMBER_PEOPLE_BORN_BETWEEN") {
            string date1, date2;
            cin >> date1 >> date2;
            auto start = born_at.lower_bound(date1);
            auto end = born_at.upper_bound(date2);
            int ans = 0;
            while (start != end) {
                ans += (*start).second;
                start++;
            }
            cout << ans << '\n';
        } else if (code == "MAX_UNRELATED_PEOPLE") {
            set<string> tried;
            cout << max_unrelated_people(citizens) << '\n';
        }
    }
}
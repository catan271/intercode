#include <bits/stdc++.h>

using namespace std;

struct citizen {
    string code;
    string birthday;
    string father;
    string mother;
    bool alive;
    string region;
};

map<string, citizen> citizens;
map<string, int> cntByBirthday;
string code, birthday, father, mother, alive, region;

void input() {
    while (true) {
        cin >> code;
        if (code == "*") {
            break;
        }

        cin >> birthday >> father >> mother >> alive >> region;
        citizen ctz;
        ctz.code = code;
        ctz.birthday = birthday;
        ctz.father = father;
        ctz.mother = mother;
        ctz.alive = alive == "Y" ? true : false;
        ctz.region = region;

        citizens[code] = ctz;
        if (cntByBirthday.count(birthday)) {
            cntByBirthday[birthday] += 1;
        } else {
            cntByBirthday[birthday] = 1;
        }
    }
}

int distanceAncestor(string code) {
    citizen ctz = citizens[code];
    int res = ctz.alive ? 0 : -1;
    if (ctz.father != "0000000") {
        int ancestor = distanceAncestor(ctz.father);
        if (ancestor >= 0)
            res = max(1 + ancestor, res);
    }
    if (ctz.mother != "0000000") {
        int ancestor = distanceAncestor(ctz.mother);
        if (ancestor >= 0)
            res = max(1 + ancestor, res);
    }
    return res;
}

void query() {
    while (true) {
        cin >> code;
        if (code == "***") {
            break;
        }

        if (code == "NUMBER_PEOPLE") {
            cout << citizens.size() << '\n';
        } else if (code == "NUMBER_PEOPLE_BORN_AT") {
            cin >> birthday;
            cout << cntByBirthday.count(birthday) ? cntByBirthday[birthday] : 0 << '\n';
        } else if (code == "MOST_ALIVE_ANCESTOR") {
            cin >> code;
            int ans = distanceAncestor(code);
            if (ans < 0) {
                ans = 0;
            }
            cout << ans << '\n';
        } else if (code == "NUMBER_PEOPLE_BORN_BETWEEN") {
            string date1;
            string date2;
            cin >> date1;
            cin >> date2;
            map<string, int>::iterator sp = cntByBirthday.lower_bound(date1);
            map<string, int>::iterator ep = cntByBirthday.upper_bound(date2);
            int cnt = 0;
            while (sp != ep) {
                cnt += (*sp).second;
                sp++;
            }
            cout << cnt << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    input();
    query();
}
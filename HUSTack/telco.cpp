#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <regex>
#include <ctime>
#include <time.h>
#include <chrono>

using namespace std;

struct Call {
    string from_number;
    string to_number;
    string date;
    string from_time;
    string end_time;
};

// Custom function to check if a phone number contains only digits
bool isPhoneNumberValid(const string& number) {
    return regex_match(number, regex("\\d{10}"));
}

// Custom function to calculate the time duration in seconds
int calculateTimeDuration(const string& from_time, const string& end_time) {
    tm tm_from = {};
    tm tm_end = {};
    strptime(from_time.c_str(), "%H:%M:%S", &tm_from);
    strptime(end_time.c_str(), "%H:%M:%S", &tm_end);

    time_t time_from = mktime(&tm_from);
    time_t time_end = mktime(&tm_end);

    return static_cast<int>(difftime(time_end, time_from));
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    set<Call> calls;
    unordered_map<string, int> phoneCallCounts;
    unordered_map<string, int> phoneCallDurations;
    int totalCalls = 0;

    string line;
    while (getline(cin, line) && line != "#") {
        if (line.find("call") != string::npos) {
            Call call;
            stringstream ss(line);
            string cmd;
            ss >> cmd >> call.from_number >> call.to_number >> call.date >> call.from_time >> call.end_time;
            if (isPhoneNumberValid(call.from_number)) {
                calls.insert(call);
                totalCalls++;
            }
        }
    }

    while (getline(cin, line) && line != "#") {
        if (line == "?check_phone_number") {
            bool allValid = true;
            for (const Call& call : calls) {
                if (!isPhoneNumberValid(call.from_number) || !isPhoneNumberValid(call.to_number)) {
                    allValid = false;
                    break;
                }
            }
            cout << (allValid ? "1" : "0") << endl;
        } else if (line.find("number_calls_from") != string::npos) {
            string phone;
            stringstream ss(line);
            string cmd;
            ss >> cmd >> phone;
            int count = 0;
            for (const Call& call : calls) {
                if (call.from_number == phone) {
                    count++;
                }
            }
            cout << count << endl;
        } else if (line == "?number_total_calls") {
            cout << totalCalls << endl;
        } else if (line.find("count_time_calls_from") != string::npos) {
            string phone;
            stringstream ss(line);
            string cmd;
            ss >> cmd >> phone;
            int duration = 0;
            for (const Call& call : calls) {
                if (call.from_number == phone) {
                    duration += calculateTimeDuration(call.from_time, call.end_time);
                }
            }
            cout << duration << endl;
        }
    }

    return 0;
}

//
// Created by kir10 on 20.10.2023.
//
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>


#define F first
#define S second

using namespace std;

class Shift {
public:
    int x, y;
    Shift() = default;
    Shift(int _x, int _y) : x(_x), y(_y) {}

    bool operator==(Shift shift) const {
        return shift.x == x && shift.y == y;
    }
};

class Position {
public:
    int x, y;
    Position() = default;
    Position(int _x, int _y) : x(_x), y(_y) {}

    Position operator+(Shift shift) const {
        Position newPosition(x + shift.x, y + shift.y);
        return newPosition;
    }

    void operator+=(Shift shift) {
        x += shift.x;
        y += shift.y;
    }

    bool operator<(Position position) const {
        return x < position.x || x == position.x && y < position.y;
    }

};

int A, B, C, K;

vector<Shift> possibleShifts = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

map<Position, vector<int>> needInfoAboutShifts;
set<Position> knownPositions;

Position currentPosition;
Shift currentShift;

int allTime;

bool IsEnd() {
    return needInfoAboutShifts.empty();
}

void ReadParams() {
    cin >> currentPosition.x >> currentPosition.y;
    cin >> currentShift.x >> currentShift.y;
    cin >> A >> B >> C >> K;
}

void AddTime(int deltaTime) {
    allTime += deltaTime;
}

void UpdateInfoAboutShifts(Position position) {
    for (int i = 0; i < 4; ++i) {
        Position shiftPosition(position + possibleShifts[i]);
        if (needInfoAboutShifts.find(shiftPosition) != needInfoAboutShifts.end()) {
            auto pointer = find(needInfoAboutShifts[shiftPosition].begin(),
                                needInfoAboutShifts[shiftPosition].end(), (i + 2) % 4);
            if (pointer != needInfoAboutShifts[shiftPosition].end()) {
                needInfoAboutShifts[shiftPosition].erase(pointer);
                if (needInfoAboutShifts[shiftPosition].empty()) {
                    needInfoAboutShifts.erase(shiftPosition);
                }
            }
        }
    }
}

void AddNewPosition(Position position, bool isFree) {
    knownPositions.insert(position);
    if (!isFree) {
        return;
    }
    vector<int> needInfoAboutPositionShifts = {0, 1, 2, 3};
    for (int i = 0; i < 4; ++i) {
        if (knownPositions.find(position + possibleShifts[i]) != knownPositions.end()) {
            needInfoAboutPositionShifts.erase(find(needInfoAboutPositionShifts.begin(),
                                                   needInfoAboutPositionShifts.end(),
                                                   i));
        }
    }
    if (!needInfoAboutPositionShifts.empty())
        needInfoAboutShifts[position] = needInfoAboutPositionShifts;
}

bool MakeMove() {
    Position newPosition = currentPosition + currentShift;
    if (knownPositions.find(newPosition) != knownPositions.end()
        && needInfoAboutShifts.find(newPosition) == needInfoAboutShifts.end())
        return false;
    cout << 1 << endl;
    AddTime(A);
    int answer;
    cin >> answer;
    return answer;
}

void MakeTurn(bool isRight) {
    cout << 2 << " " << isRight << endl;
    for (int i = 0; i < 4; ++i) {
        if (possibleShifts[i] == currentShift) {
            if (isRight) {
                currentShift = possibleShifts[(i + 3) % 4];
            } else {
                currentShift = possibleShifts[(i + 1) % 4];
            }

            AddTime(B);
            break;
        }
    }
    int answer;
    cin >> answer;
}

void DoAction() {
    bool isMoved = MakeMove();
    if (knownPositions.find(currentPosition + currentShift) == knownPositions.end()) {
        AddNewPosition(currentPosition + currentShift, isMoved);
    }
    UpdateInfoAboutShifts(currentPosition + currentShift);
    if (isMoved) {
        currentPosition += currentShift;
        if (IsEnd()) {
            return;
        }
        MakeTurn(true);
        return;
    }
    if (IsEnd()) {
        return;
    }
    MakeTurn(false);
}

int main() {
    ReadParams();
    needInfoAboutShifts[currentPosition] = {0, 1, 2, 3};
    knownPositions.insert(currentPosition);
    while (!IsEnd()) {
        DoAction();
    }
    cout << allTime;
}
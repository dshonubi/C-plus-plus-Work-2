/* Please note: even though it says IMPLEMENT ME, in some cases
   the implementation can be empty. In fact, you may wish to remove
   some of the functions entirely
*/
#include "Football.h"

// -------------- Team --------------------

Team::Team(const string& name) {
	_team = name;
	_goalsConceded = 0;
}

void Team::addGoalsConceded(int g) {
	_goalsConceded += g;
}

// -------------- Player ------------------


Player::Player(const string& name, Team* t) {
	_getScore = 0;
	_goalsScored = 0;
	_goalsAssisted = 0;
	_playerName = name;
	_goalsConceded = &t->_goalsConceded;
}

// don't remove this even if you want to make the destructor pure virtual
Player::~Player() {
	// IMPLEMENT ME
}

void Player::addAssists(int a) {
	_goalsAssisted = a;
	_getScore += (_goalsAssisted * 3);
}
// -------------- Attacker ------------------

Attacker::Attacker(const string& name, Team* t) : Player(name, t) {
	_getScore = 0;
	_goalsAssisted = 0;
	_goalsScored = 0;
	_playerName = name;
	_goalsConceded = &t->_goalsConceded;
	_teamName = t->_team;
}

void Attacker::addGoalsScored(int g) {
	_goalsScored = g;
	_getScore += (_goalsScored * 4);
}

int Attacker::getScore() const {
	return _getScore;
}

string Attacker::print() const {
	string fprint = "";
	string gs = to_string(_goalsScored);
	string ga = to_string(_goalsAssisted);
	string gc = to_string(*_goalsConceded);
	string gcs = to_string(getScore());

	fprint += "Attacker: " + _playerName + ", Team: " + _teamName + "\n";
	fprint += " Goals scored: " + gs + "\n";
	fprint += " Assists: " + ga + "\n";
	fprint += " Goals conceded: " + gc + "\n";
	fprint += " Score: " + gcs;
	return fprint;
}

// -------------- Midfielder ------------------

Midfielder::Midfielder(const string& name, Team* t) : Player(name, t) {
	_getScore = 1;
	_goalsAssisted = 0;
	_goalsScored = 0;
	_playerName = name;
	_goalsConceded = &t->_goalsConceded;
	_teamName = t->_team;
}

void Midfielder::addGoalsScored(int g) {
	_goalsScored = g;
	_getScore += (_goalsScored * 5);
}

int Midfielder::getScore() const {
	int getScore = 0;
	getScore = _getScore;
	if (*_goalsConceded > 0)
		--getScore;
	return getScore;
}

string Midfielder::print() const {
	string fprint = "";
	string gs = to_string(_goalsScored);
	string ga = to_string(_goalsAssisted);
	string gc = to_string(*_goalsConceded);
	string gcs = to_string(getScore());

	fprint += "Midfielder: " + _playerName + ", Team: " + _teamName + "\n";
	fprint += " Goals scored: " + gs + "\n";
	fprint += " Assists: " + ga + "\n";
	fprint += " Goals conceded: " + gc + "\n";
	fprint += " Score: " + gcs;
	return fprint;
}

// -------------- Defender ------------------

Defender::Defender(const string& name, Team* t) : Player(name, t) {
	_getScore = 4;
	_goalsAssisted = 0;
	_goalsScored = 0;
	_playerName = name;
	_goalsConceded = &t->_goalsConceded;
	_teamName = t->_team;
}


void Defender::addGoalsScored(int g) {
	_goalsScored = g;
	_getScore += (_goalsScored * 6);
}

int Defender::getScore() const {
	int getScore = 0;
	getScore = _getScore;

	if (*_goalsConceded > 0)
		getScore -= 4;

	getScore -= (*_goalsConceded / 2);
	return getScore;
}

string Defender::print() const {
	string fprint = "";
	string gs = to_string(_goalsScored);
	string ga = to_string(_goalsAssisted);
	string gc = to_string(*_goalsConceded);
	string gcs = to_string(getScore());

	fprint += "Defender: " + _playerName + ", Team: " + _teamName + "\n";
	fprint += " Goals scored: " + gs + "\n";
	fprint += " Assists: " + ga + "\n";
	fprint += " Goals conceded: " + gc + "\n";
	fprint += " Score: " + gcs;
	return fprint;
}

// -------------- Goalkeeper ------------------

Goalkeeper::Goalkeeper(const string& name, Team* t) : Player(name, t) {
	_getScore = 4;
	_goalsAssisted = 0;
	_goalsScored = 0;
	_playerName = name;
	_goalsConceded = &t->_goalsConceded;
	_teamName = t->_team;
	_goalsSaved = 0;
}

void Goalkeeper::addGoalsScored(int g) {
	_goalsScored = g;
	_getScore += (_goalsScored * 6);
}

void Goalkeeper::addShotsSaved(int ss) {
	_goalsSaved += ss;
	_getScore += (_goalsSaved / 3);
}

int Goalkeeper::getScore() const {
	int getScore = 0;
	getScore = _getScore;

	if (*_goalsConceded > 0)
		getScore -= 4;

	getScore -= (*_goalsConceded / 2);
	return getScore;
}

string Goalkeeper::print() const {
	string fprint = "";
	string gs = to_string(_goalsScored);
	string ga = to_string(_goalsAssisted);
	string gc = to_string(*_goalsConceded);
	string ss = to_string(_goalsSaved);
	string gcs = to_string(getScore());

	fprint += "Goalkeeper: " + _playerName + ", Team: " + _teamName + "\n";
	fprint += " Goals scored: " + gs + "\n";
	fprint += " Assists: " + ga + "\n";
	fprint += " Goals conceded: " + gc + "\n";
	fprint += " Shots saved: " + ss + "\n";
	fprint += " Score: " + gcs;
	return fprint;
}

// -------------- FantasyTeam ------------------

FantasyTeam::FantasyTeam() {
	_fantasyTeam = 0;
	for (int i = 0; i < 11; i++) {
		players[i] = nullptr;
	}
}

bool FantasyTeam::addPlayer(Player* p) {
	if (_fantasyTeam > 10)
		return false;

	for (int i = 0; i < _fantasyTeam; i++) {
		if (players[i] == p) {
			return false;
		}
	}
	players[_fantasyTeam] = p;
	++_fantasyTeam;
	return true;

}

int FantasyTeam::getScore() const {
	int _getScore = 0;
	for (int i = 0; i < _fantasyTeam; i++) {
		_getScore += players[i]->getScore();
	}
	return _getScore;
}

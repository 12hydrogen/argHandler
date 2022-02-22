#pragma once

#include <cstring>

#include <iostream>
#include <iomanip>

#include <algorithm>
#include <string>
#include <vector>
#include <map>

#define HELP_VALUE_WIDTH 24
#define HELP_SPACE_WIDTH 8

using namespace std;

typedef vector<string>::const_iterator cbFuncArg;
typedef int (*cbFunc)(cbFuncArg curArg, cbFuncArg endArg);

class arg;

class handler
{
private:
	map<arg, cbFunc> argList;

	bool withPrefix;
	char prefix;

	bool isRestrict;

	void help(bool contentOnly = false, int spacesCount = HELP_SPACE_WIDTH) const;
	void exec(vector<string> argvs) const;
public:
	handler(const handler &copy) = default;
	handler(handler &&copy) = default;
	~handler() = default;

	handler(bool withPrefix = true, bool isRestrict = false, char prefix = '-');
	handler(const vector<arg> &arg, const vector<cbFunc> &func, bool withPrefix = true, bool isRestrict = false, char prefix = '-');

	void append(arg argu, cbFunc func);
	void change(arg argu, cbFunc func);
	void remove(arg argu);

	void exec(int argc, char **argv) const;

	friend arg;
};

class arg
{
private:
	string value;
	string explain;

	bool isSimple;
	handler subArg;
public:
	arg(const arg &copy) = default;
	arg(arg &&copy) = default;
	~arg() = default;

	arg(bool isSimple = true);
	arg(const string &value, const string &explain, bool isSimple = true);
	arg(string &&value, string &&explain, bool isSimple = true);
	arg(const string &value, const string &explain, const handler &subArg, bool isSimple = true);
	arg(string &&value, string &&explain, const handler &subArg, bool isSimple = true);

	void setExp(const string &exp);
	void setExp(string &&exp);
	const string& getValue() const;

	friend handler;
};

bool operator<(const arg &a, const arg &b);
bool operator>(const arg &a, const arg &b);
bool operator<=(const arg &a, const arg &b);
bool operator>=(const arg &a, const arg &b);
bool operator==(const arg &a, const arg &b);
bool operator!=(const arg &a, const arg &b);

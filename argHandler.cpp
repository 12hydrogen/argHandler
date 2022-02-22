#include "argHandler.hpp"

arg::arg(bool isSimple/* = true*/):
isSimple(isSimple)
{}
arg::arg(const string &value, const string &explain, bool isSimple/* = true*/):
value(value), explain(explain), isSimple(isSimple)
{}
arg::arg(string &&value, string &&explain, bool isSimple/* = true*/):
value(value), explain(explain), isSimple(isSimple)
{}
arg::arg(const string &value, const string &explain, const handler &subArg, bool isSimple/* = true*/):
value(value), explain(explain), subArg(subArg), isSimple(isSimple)
{}
arg::arg(string &&value, string &&explain, const handler &subArg, bool isSimple/* = true*/):
value(value), explain(explain), subArg(subArg), isSimple(isSimple)
{}

void arg::setExp(const string &exp)
{
	explain = exp;
}
void arg::setExp(string &&exp)
{
	explain = exp;
}
const string& arg::getValue() const
{
	return value;
}

handler::handler(bool withPrefix/* = true*/, bool isRestrict/* = false*/, char prefix/* = '-'*/):
withPrefix(withPrefix), isRestrict(isRestrict), prefix(prefix)
{}
handler::handler(const vector<arg> &arg, const vector<cbFunc> &func, bool withPrefix/* = true*/, bool isRestrict/* = false*/, char prefix/* = '-'*/):
withPrefix(withPrefix), isRestrict(isRestrict), prefix(prefix)
{}

void handler::help(bool contentOnly/* = false*/, int spacesCount/* = HELP_SPACE_COUNT*/) const
{
	if (!contentOnly)
	{
		cout << "\n";
		cout << "Shell argument handler\n";
		cout << "Author : 12hydrogen\n\n";
	}
	for (auto &cur : argList)
	{
		for (int i = 0; i < spacesCount; i++)
			cout << " ";
		if (withPrefix)
		{
			if (cur.first.value.size() <= 1)
			{
				cout << " " << prefix << left << setw(HELP_VALUE_WIDTH) << cur.first.value;
			}
			else
			{
				cout<< prefix << prefix << left << setw(HELP_VALUE_WIDTH) << cur.first.value;
			}
		}
		else
		{
			cout << left << setw(HELP_VALUE_WIDTH) << cur.first.value;
		}
		cout.flush();
		for (int i = 0; i < HELP_SPACE_WIDTH; i++)
			cout << " ";
		cout << cur.first.explain << "\n";
		if (!cur.first.isSimple)
		{
			cout << "\n";
			cur.first.subArg.help(true, spacesCount + HELP_SPACE_WIDTH);
			cout << "\n";
		}
	}
}
void handler::exec(int argc, char **argv) const
{
	vector<string> argvs;
	for (int i = 1; i < argc; i++)
	{
		char *begPos = argv[i];
		if (withPrefix)
		{
			if (strlen(begPos) <= 2)
			{
				if (begPos[0] == prefix)
					begPos += 1;
			}
			else
			{
				if (begPos[0] == prefix && begPos[1] == prefix)
					begPos += 2;
			}
		}
		argvs.emplace_back(string(begPos));
	}
	exec(argvs);
}
void handler::exec(vector<string> argvs) const
{
	string helpStr("help");
	for (auto &arg : argvs)
	{
		if (arg == helpStr)
		{
			help();
			return;
		}
	}
	if (isRestrict)
	{
		bool nextLevel = false;
		bool hit = false;
		for (auto &arg : argvs)
		{
			hit = false;
			for (auto &cur : argList)
			{
				if (arg == cur.first.value)
				{
					if (nextLevel)
						nextLevel = false;
					if (!cur.first.isSimple)
						nextLevel = true;
					hit = true;
					break;
				}
			}
			if (!nextLevel && !hit)
			{
				cout << "Can't recognize argument " << arg << "\n";
				return;
			}
		}
	}

	bool nextLevel = false;
	const handler *nextHandler = NULL;
	auto begPos = argvs.begin();
	auto arg = argvs.begin();
	auto argEnd = argvs.end();
	for (; arg < argEnd; ++arg)
	{
		auto cur = argList.begin();
		auto end = argList.end();
		for (; cur != end; ++cur)
		{
			if (cur->first.value == *arg)
			{
				if (nextLevel)
				{
					nextHandler->exec(vector<string>(begPos, arg));
					nextLevel = false;
				}
				if (cur->first.isSimple)
				{
					if (cur->second != NULL)
					{
						arg += cur->second(arg, argEnd);
					}
				}
				else
				{
					nextLevel = true;
					nextHandler = &(cur->first.subArg);
					begPos = arg + 1;
				}
				break;
			}
		}
	}
	if (nextLevel)
	{
		nextHandler->exec(vector<string>(begPos, arg));
	}
}

void handler::append(arg argu, cbFunc func)
{
	argList.insert(make_pair(argu, func));
}
void handler::change(arg argu, cbFunc func)
{
	argList.find(argu)->second = func;
}
void handler::remove(arg argu)
{
	argList.erase(argu);
}

bool operator<(const arg &a, const arg &b)
{
	return a.getValue() < b.getValue();
}
bool operator>(const arg &a, const arg &b)
{
	return a.getValue() > b.getValue();
}
bool operator<=(const arg &a, const arg &b)
{
	return a.getValue() <= b.getValue();
}
bool operator>=(const arg &a, const arg &b)
{
	return a.getValue() >= b.getValue();
}
bool operator==(const arg &a, const arg &b)
{
	return a.getValue() == b.getValue();
}
bool operator!=(const arg &a, const arg &b)
{
	return a.getValue() != b.getValue();
}

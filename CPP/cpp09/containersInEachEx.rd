found with command : grep -R --include=\*.{cpp,hpp} -E "std::(vector|list|deque|map|set|queue|stack|priority_queue)<" .

ex00 ==> 
	std::map<>
==> 
./main.cpp:std::map<std::string, double> loadDatabase(const std::string& dbFile) {
./main.cpp:    std::map<std::string, double> database;
./main.cpp:bool findClosestDateAndValue(const std::string &targetDate, const std::map<std::string, double> &database, double &foundValue) {
./main.cpp:    for (std::map<std::string, double>::const_iterator it = database.begin(); it != database.end(); ++it) {
./main.cpp:bool findDateInDbAndCalcVal(const std::string &dateAndAmount, const std::map<std::string, double> &database) {
./main.cpp:    std::map<std::string, double> database = loadDatabase(dbFile);

ex01 ==> 
	std::stack 
==> 
./RPN.cpp:      std::stack<double>      stack;

ex02 ==> 
	std::qeue 
	std::vector
	std::list
==> 


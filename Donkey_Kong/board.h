#pragma once
class Board {
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;
	const char* originalBoard[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                     (      )                 Q", // 1
		  "Q  OO         !                                     (           )              Q", // 2
		  "Q  OO   &     $                                       (       )                Q", // 3
		  "Q =====================                                  (   )                 Q", // 4
		  "Q                   H                                     ----                 Q", // 5
		  "Q                   H                                                          Q", // 6
		  "Q         >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                          Q", // 7
		  "Q                                 H                                            Q", // 8
		  "Q                                 H                               O            Q", // 9
		  "Q                                 H                               |            Q", // 10
		  "Q                         <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<           Q", // 11
		  "Q         O                                       H                            Q", // 12
		  "Q         |                                       H                            Q", // 13
		  "Q       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                            Q", // 14
		  "Q                            H                                                 Q", // 15
		  "Q                            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>       Q", // 16
		  "Q          ( )                                           H                     Q", // 17
		  "Q        (   )                                           H                     Q", // 18
		  "Q         ( )      <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<        *          Q", // 19
		  "Q         _||                                  H                   / `         Q", // 20
		  "Q        /___`                                 H                  /   `        Q", // 21
		  "Q       /_____`                                H                 /_____`       Q", // 22
		  "Q       |   []|                                H                    |          Q", // 23
		  "================================================================================"  // 24
	};
	char currentBoard[MAX_Y][MAX_X + 1]; // +1 for null terminator
public:
	void reset();
	void print() const;
	char getChar(int x, int y) const {
		return currentBoard[y][x];
	}
};


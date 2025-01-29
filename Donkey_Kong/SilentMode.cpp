#include "SilentMode.h"
void SilentMode::printTimeScore() {
	scoreIterationCount++;
	if (scoreIterationCount >= iterationUntilSec) {
		GameTime++;
		scoreIterationCount = 0;
	}
}
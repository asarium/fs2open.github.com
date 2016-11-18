
#include "scripting/ScriptingTestFixture.h"

class RequireTest : public test::scripting::ScriptingTestFixture {
 public:
	RequireTest() : test::scripting::ScriptingTestFixture(0) {
		pushModDir("require");
	}
};

TEST_F(RequireTest, defaultRequire) {
	this->EvalTestScript();
}

TEST_F(RequireTest, overrideRequire) {
	this->EvalTestScript();
}


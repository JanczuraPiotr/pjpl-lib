/*
 * File:   DateTimeTest.cpp
 * Author: Piotr Janczura <piotr@janczura.pl>
 *
 * Created on 2018-05-27, 15:15:09
 */

#include "MacroExpressionTest.h"

#include "../../libs/napisy.h"
#include "../../model/db/def.h"
#include "../../model/db/DB.h"
#include "../../model/db/Driver.h"
#include "../../model/Monitors.h"
#include "../../model/ParamsForFilter.h"

#include "model/ParamsForFilterTest.h"


CPPUNIT_TEST_SUITE_REGISTRATION(MacroExpressionTest);

MacroExpressionTest::MacroExpressionTest() {
}

MacroExpressionTest::~MacroExpressionTest() {
}

void MacroExpressionTest::setUp() {
    std::shared_ptr<pjpl::db::Query> query = pjpl::db::DB::i()->getDriver().getQuery();
    query->update("TRUNCATE zm.Monitors");
    std::string sql =
            "INSERT INTO Monitors (Id, `Name`, `Function`, `profiles`, `ModbusOutputId`) "
            "VALUES (:Id:, :Name:, :Function:, 0, 0)";
    query->update(sql, {
            {"Id",       std::to_string(1)},
            {"Name",     "Monitor1"},
            {"Function", "Smart Recording"}
    });
    query->update(sql, {
            {"Id",       std::to_string(2)},
            {"Name",     "Monitor2"},
            {"Function", "Smart Recording"}
    });
    query->update(sql, {
            {"Id",       std::to_string(3)},
            {"Name",     "Monitor3"},
            {"Function", "Smart Watch"}
    });
    query->update(sql, {
            {"Id",       std::to_string(4)},
            {"Name",     "Monitor4"},
            {"Function", "Intrusion Trace"}
    });
    query->update(sql, {
            {"Id",       std::to_string(5)},
            {"Name",     "Monitor5"},
            {"Function", "Smart Watch"}
    });
    query->update(sql, {
            {"Id",       std::to_string(6)},
            {"Name",     "Monitor6"},
            {"Function", "Intrusion Trace"}
    });
    query->update(sql, {
            {"Id",       std::to_string(7)},
            {"Name",     "Monitor7"},
            {"Function", "None"}
    });
    query->update(sql, {
            {"Id",       std::to_string(8)},
            {"Name",     "Monitor8"},
            {"Function", "None"}
    });
    query->update(sql, {
            {"Id",       std::to_string(9)},
            {"Name",     "Monitor9"},
            {"Function", "Smart Recording"}
    });
    query->update(sql, {
            {"Id",       std::to_string(10)},
            {"Name",     "Monitor10"},
            {"Function", "Intrusion Trace"}
    });
    // none 7,8
    // sr   1,2,9
    // sw   3,5
    // it   4,6,10
}

void MacroExpressionTest::tearDown() {
    std::shared_ptr<pjpl::db::Query> query = pjpl::db::DB::i()->getDriver().getQuery();
    query->update("truncate Monitors");

}

void MacroExpressionTest::test1() {
    std::wstring conditionsCompiled = L"<\">Cause<\"/> = <\">Intrusion<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1",//  int,
                "", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );

    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "", //  monitorId,
                "", //  name,
                "Intrusion", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Cause=Intrusion / EVENT : Cause=Intrusion ", result);
}
void MacroExpressionTest::test2() {
    std::wstring conditionsCompiled = L"<\">Cause<\"/> = <\">Intrusion<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "", //  monitorId,
                "", //  name,
                "LPR", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Cause=Intrusion / EVENT : Cause=LPR", !result);
}
void MacroExpressionTest::test3() {
    std::wstring conditionsCompiled = L"<\"> MonitorId <\"/>=<\">1<\"/> or<\">Person <\"/> = <\">11<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );

    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "11", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                ""  //  allowance
    );
    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE(" MACRO : MonitorId=1 or Person=11 / EVENT: MonitorId=1 / Person=11 ", result);
}
void MacroExpressionTest::test4() {
    std::wstring conditionsCompiled  = L"<\"> MonitorId <\"/>=<\">1<\"/> or<\">Person <\"/> = <\">11<\"/>";

    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );

    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1",//  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "1", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : MonitorId=1 or Person=11 / EVENT : MonitorId=1, Person = 1 ", result);
}
void MacroExpressionTest::test5() {
    std::wstring conditionsCompiled  = L"<\"> MonitorId <\"/>=<\">1<\"/> and<\">Person <\"/> = <\">11<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "1", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO MonitorId=1 and Person=11 / EVENT : MonitorId=1, Person=1", !result);
}
void MacroExpressionTest::test6() {
    std::wstring conditionsCompiled  = L"<\"> MonitorId <\"/>=<\">1<\"/> or<\">Person <\"/> != <\">11<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "11", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO MonitorId=1 or Person!=11 / EVENT : MonitorId=1, Person!=11", result);
}
void MacroExpressionTest::test7() {
    std::wstring conditionsCompiled  = L"<\"> MonitorId <\"/>=<\">1<\"/> or<\">Person <\"/> != <\">11<\"/>";

    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );

    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "2", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "11", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE(" MonitorId=1 or Person!=11 / MonitorId = 2, Person=11" ,!result);
}
void MacroExpressionTest::test8() {
    std::wstring conditionsCompiled  = L"<\"> MonitorId <\"/>=<\">1<\"/> or<\">Person <\"/> != <\">11<\"/>";

    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );

    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "2", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "1", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : MonitorId=1 or Person!=11 / EVENT : MonitorId=2, Person=1" ,result);
}
void MacroExpressionTest::test9() {
    std::wstring conditionsCompiled  = L"<\">MonitorId <\"/> =[<\">1<\"/>,<\">2<\"/>,<\">3<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO MonitorId =[ <\">1<\"/>, <\">2<\"/> ,<\">3<\"/>] / EVENT : MonitorId=1", result);
}
void MacroExpressionTest::test10() {
    std::wstring conditionsCompiled  = L"<\">MonitorId<\"/> =[<\">1<\"/>,<\">2<\"/>,<\">3<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "5", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : MonitorId =[ 1, 2,3 ] / EVENT : MonitorId=5", !result);
}
void MacroExpressionTest::test11() {
    std::wstring conditionsCompiled  = L"<\">Person<\"/> =[<\">11<\"/>,<\">12<\"/>,<\">-3<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "11", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Person=[11,12,-3] / EVENT : Person=11", result);
}
void MacroExpressionTest::test12() {
    std::wstring conditionsCompiled  = L"<\">Person<\"/> =[<\">11<\"/>,<\">12<\"/>,<\">-3<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );

    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "-3", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Person=[11,12,-3] / EVENT : Person=-3", result);
}
void MacroExpressionTest::test13() {
    std::wstring conditionsCompiled  = L"<\">Person<\"> =[<\">11<\"/>,<\">12<\"/>,<\">-3<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );

    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "100", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Person=[11,12,-3] / EVENT : Person=100", !result);
}
void MacroExpressionTest::test14() {
    std::wstring conditionsCompiled  = L"<\">Person<\"/> =[<\">11<\"/>,<\">12<\"/>,<\">-3<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Person=[11,12,-3] / EVENT : Person=brak", !result);
}
void MacroExpressionTest::test15() {
    std::wstring conditionsCompiled  = L"<\">MonitorId<\"/> ![<\">1<\"/>,<\">2<\"/>,<\">3<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "5", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : MonitorId\" ![ 1, 2, 3 ] / EVENT : MonitorId=5", result);
}
void MacroExpressionTest::test16() {
    std::wstring conditionsCompiled  = L"<\">Person<\"/> ![<\">11<\"/>,<\">12<\"/>,<\">-3<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "11", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Person![11,12,-3] / EVENT : Person=11", !result);
}
void MacroExpressionTest::test17() {
    std::wstring conditionsCompiled  = L"<\">Person<\"/> ![<\">11<\"/>,<\">12<\"/>,<\">-3<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "-3", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Person![11,12,-3] / EVENT : Person=-3", !result);
}
void MacroExpressionTest::test18() {
    std::wstring conditionsCompiled  = L"<\">Person<\"/> ![<\">11<\"/>,<\">12<\"/>,<\">-3<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "100", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Person![11,12,-3] / EVENT : Person=100", result);
}
void MacroExpressionTest::test19() {
    std::wstring conditionsCompiled  = L"<\">Person<\"/> ![<\">11<\"/>,<\">12<\"/>,<\">-3<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Person![11,12,-3] / EVENT : Person=brak", !result);
}
void MacroExpressionTest::test20() {
    std::wstring conditionsCompiled  = L"<\">MonitorId<\"/> =<\">1<\"/>  and  <\">Person<\"/> =[<\">11<\"/>,<\">12<\"/>,<\">-3<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "11", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO MonitorId =[ 1, 2 ] and Person=[11,12,-3] / EVENT : MonitorId=1, Person=11" , result);
}
void MacroExpressionTest::test21() {
    std::wstring conditionsCompiled  = L"<\">MonitorId<\"/> =[ <\">1<\"/>, <\">2 <\"/>]  and  <\">Person<\"/> =[<\">11<\"/>,<\">12<\"/>,<\">-3<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "11", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO MonitorId=[ 1, 2 ] and Person=[11,12,-3] / EVENT : MonitorId=1, Person=11", result);
}
void MacroExpressionTest::test22() {
    std::wstring conditionsCompiled  = L"<\">PlateId<\"/> =<\">1<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "1", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO PlateId = 1 / EVENT : PlateId=1", result);
}
void MacroExpressionTest::test23() {
    std::wstring conditionsCompiled  = L"<\">PlateId<\"/> =[<\">1<\"/>,<\">2<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "1,2,3", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO PlateId=[ 1, 2 ]  / EVENT : PlateId = 1,2,3", result);
}
void MacroExpressionTest::test24() {
    std::wstring conditionsCompiled  = L"<\">PlateId<\"/> =[<\">1<\"/>,<\">2<\"/>,<\">3<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "1,2", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO PlateId=[ 1, 2,3 ]  / EVENT : PlateId = 1,2", result);
}
void MacroExpressionTest::test25() {
    std::wstring conditionsCompiled  = L"<\">Person<\"/> =[<\">1<\"/>,<\">2<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "3,1", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO PlateId=[ 1, 2]  / EVENT : PlateId = 1,3", result);
}
void MacroExpressionTest::test26() {
    std::wstring conditionsCompiled  = L"<\">PlateId<\"/> =[<\">1<\"/>,<\">2<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "3,4", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO PlateId=[ 1, 2]  / EVENT : PlateId = 3,4", !result);
}
void MacroExpressionTest::test27() {
    std::wstring conditionsCompiled  = L"<\">PlateId<\"/> ![<\">1<\"/>,<\">2<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "1,2", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO PlateID ![ 1, 2 ] / EVENT : PlateId=1,2", !result);
}
void MacroExpressionTest::test28() {
    std::wstring conditionsCompiled  = L"<\">PlateId<\"/> ![<\">1<\"/>,<\">2<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "1", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO PlateID ![ 1, 2 ] / EVENT : PlateId=1", !result);
}
void MacroExpressionTest::test29() {
    std::wstring conditionsCompiled  = L"<\">PlateId<\"/> ![<\">1<\"/>,<\">2<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "1,3", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO PlateID ![ 1, 2 ] / EVENT : PlateId=1,3", result);
}
void MacroExpressionTest::test30() {
    std::wstring conditionsCompiled  = L"<\">PlateId<\"/> ![<\">1<\"/>,<\">2<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "3,4", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO PlateID ![ 1, 2 ] / EVENT : PlateId=3,4", result);
}
void MacroExpressionTest::test31() {
    std::wstring conditionsCompiled  = L"<\">PlateId<\"/> =[<\">1<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "1", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO PlateId =[ 1] / EVENT : PlateId=1", result);
}
void MacroExpressionTest::test32() {
    std::wstring conditionsCompiled  = L"<\">PlateId<\"/> ![<\">1<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "1", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO PlateID ![ 1 ] / EVENT : PlateId=1", !result);
}
void MacroExpressionTest::test33() {
    std::wstring conditionsCompiled  = L"<\">PlateId<\"/> =[<\">1<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "2", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO PlateId =[ 1] / EVENT : PlateId=2", !result);
}
void MacroExpressionTest::test34() {
    std::wstring conditionsCompiled  = L"<\">PlateId<\"/> =[<\">1<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "1", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO PlateID ![ 1 ] / EVENT : PlateId=1", result);
}
void MacroExpressionTest::test35() {
    std::wstring conditionsCompiled  = L"<\">PlateId<\"/> =[<\">1<\"/>,<\">2<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1",//  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "3,4", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO PlateID =[ 1, 2 ] / EVENT : PlateId=3,4", !result);
}
void MacroExpressionTest::test36() {
    std::wstring conditionsCompiled  = L"<\">PlateId<\"/> ![<\">1<\"/>,<\">2<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "2,3", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO PlateID ![ 1, 2 ] / EVENT : PlateId=2,3", result);
}
void MacroExpressionTest::test37() {
    std::wstring conditionsCompiled  = L"<\">PlateId<\"/> ![<\">1<\"/>,<\">2<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "1,2", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO PlateID ![ 1, 2 ] / EVENT : PlateId=1,2", !result);
}
void MacroExpressionTest::test38() {
    std::wstring conditionsCompiled  = L"<\">PlateId<\"/> ![<\"/>1<\"/>,<\">2<\"/>]";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "2", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO PlateID ![ 1, 2 ] / EVENT : PlateId=2", !result);
}
void MacroExpressionTest::test39() {
    std::wstring conditionsCompiled  = L"<\">Cause<\"/> = <\">Smart recording<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "", //  monitorId,
                "", //  name,
                "Smart recording", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Cause=\"Smart recording\" / EVENT : Cause=\"Smart recording\" ", result);
}
void MacroExpressionTest::test40() {
    std::wstring conditionsCompiled  = L"<\">Cause<\"/> = <\">Smart recording<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "", //  monitorId,
                "", //  name,
                "LPR", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Cause=\"Smart recording\" / EVENT : Cause=LPR", !result);
}
void MacroExpressionTest::test41() {
    std::wstring conditionsCompiled  = L"<\">StartDateTime<\"/> = <\">2018-08-10 12:41:00<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "2018-08-10 12:41:00", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : StartDateTime=\"2018-08-10 12:41:00\" / EVENT : StartDateTime = 2018-08-10 12:41:00", result);
}
// deleted void MacroExpressionTest::test42()
// deleted void MacroExpressionTest::test42()
void MacroExpressionTest::test44() {
    std::wstring conditionsCompiled  = L"<\">LprDirection<\"/> = <\">Incoming<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "Incoming", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : LprDirection=\"Incoming\" / EVENT : LprDirection = Incoming", result);
}
void MacroExpressionTest::test45() {
    std::wstring conditionsCompiled = L"<\">Allowance<\"/> = <\">0<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
        = std::make_shared<pjpl::model::EventToServeRecord>(
                "", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "0"  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Allowance=\"0\" / EVENT : Allowance = 0", result);
}
void MacroExpressionTest::test46() {
    std::wstring conditionsCompiled  = L"<\">MonitorFunction<\"/> = <\">None<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "2", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);
    params.setParam(L"MonitorFunction", L"None");

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);
    CPPUNIT_ASSERT_MESSAGE("MACRO : MonitorFunction=\"None\" / EVENT : MonitorFunction = None", result);
}
void MacroExpressionTest::test47() {
    std::wstring conditionsCompiled  = L"<\">MonitorFunction<\"/> = <\">Smart Watch<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "2", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                ""  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);
    params.setParam(L"MonitorFunction", L"Smart Watch");

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);
    CPPUNIT_ASSERT_MESSAGE("MACRO : MonitorFunction=\"Smart Watch\" / EVENT : MonitorFunction = Smart Watch", result);
}
void MacroExpressionTest::test48() {
    std::wstring conditionsCompiled  = L"<\">Notes<\"/> = <\">1234<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "1234", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "0"  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Notes=\"1234 / EVENT : Notes = 1234", result);
}
void MacroExpressionTest::test49() {
    std::wstring conditionsCompiled  = L"<\">Notes<\"/> = <\">ABCD 1234<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, // conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "", //  monitorId,
                "", //  name,
                "", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "ABCD 1234", // notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "0"  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Notes=ABCD 1234 / EVENT : Notes = ABCD 1234", result);
}
void MacroExpressionTest::test50() {
    std::wstring conditionsCompiled  = L"<\">Notes<\"/> = <\">Jakieś coś się wydarzyło !<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                L"<\">Notes<\"/> = <\">Jakieś coś się wydarzyło !<\"/>", //conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                L"", //  monitorId,
                L"", //  name,
                L"", //  cause,
                L"", //  userCause,
                L"", //  startDateTime,
                L"", //  endDateTime,
                L"Jakieś coś się wydarzyło !", //  notes,
                L"", //  recognition,
                L"", //  person,
                L"", //  faceType,
                L"", //  lprDirection,
                L"", //  variableId,
                L"", //  variableVal,
                L"", //  sourceEventId,
                L"", //  sourceEventName,
                L"", //  voivodship,
                L"", //  district,
                L"", //  platetype,
                L"", //  plateId,
                L"0"  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE(
            "MACRO : Notes=\"Jakieś coś się wydarzyło !\" / EVENT : Notes = 'Jakieś coś się wydarzyło !'"
            , result);
}
void MacroExpressionTest::test51() {
    std::wstring conditionsCompiled  = L"<\">Notes<\"/> = <\">żadne coś się nie wydarzyło , albo - może jednak ?<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                L"", //  monitorId,
                L"", //  name,
                L"", //  cause,
                L"", //  userCause,
                L"", //  startDateTime,
                L"", //  endDateTime,
                L"żadne coś się nie wydarzyło , albo - może jednak ?", //  notes,
                L"", //  recognition,
                L"", //  person,
                L"", //  faceType,
                L"", //  lprDirection,
                L"", //  variableId,
                L"", //  variableVal,
                L"", //  sourceEventId,
                L"", //  sourceEventName,
                L"", //  voivodship,
                L"", //  district,
                L"", //  platetype,
                L"", //  plateId,
                L"0"  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Notes=\"żadne coś się nie wydarzyło , albo - może jednak ?\" / EVENT : Notes = żadne coś się nie wydarzyło , albo - może jednak ?", result);
}

void MacroExpressionTest::test52() {
    std::wstring conditionsCompiled  = L"<\">Notes<\"/> = <\">powiedział : \"ęą śłż źćń\", a potem : \"ĘĄŚ ŁŻŹ ĆŃ\" ?<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1", //  int,
                "Name", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );
    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                L"1", //  monitorId,
                L"", //  name,
                L"", //  cause,
                L"", //  userCause,
                L"", //  startDateTime,
                L"", //  endDateTime,
                L"powiedział : \"ęą śłż źćń\", a potem : \"ĘĄŚ ŁŻŹ ĆŃ\" ?", //  notes,
                L"", //  recognition,
                L"", //  person,
                L"", //  faceType,
                L"", //  lprDirection,
                L"", //  variableId,
                L"", //  variableVal,
                L"", //  sourceEventId,
                L"", //  sourceEventName,
                L"", //  voivodship,
                L"", //  district,
                L"", //  platetype,
                L"", //  plateId,
                L"0"  //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Notes=\" \"powiedział : \"ęą śłż źćń\", a potem : \"ĘĄŚ ŁŻŹ ĆŃ\" ?\" / EVENT : Notes = powiedział : ęą śłż źćń, a potem : ĘĄŚ ŁŻŹ ĆŃ ?", result);
}

void MacroExpressionTest::test53() {
    std::wstring conditionsCompiled = L"<\">Cause<\"/> = <\">Intrusion<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                "1",//  int,
                "", //  name,
                "", //  conditionsJson,
                conditionsCompiled, //  conditionCompiled,
                "", //  actionType,
                "", //  actionOut,
                "", //  action,
                "", //  actionType2,
                "", //  actionOut2,
                "", //  action2,
                "", //  actionType3,
                "", //  actionOut3,
                "", //  action3,
                "", //  autoExecute,
                "", //  autoExecuteCmd,
                ""  //  message
    );

    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                "1", //  monitorId,
                "", //  name,
                "Null", //  cause,
                "", //  userCause,
                "", //  startDateTime,
                "", //  endDateTime,
                "", //  notes,
                "", //  recognition,
                "", //  person,
                "", //  faceType,
                "", //  lprDirection,
                "", //  variableId,
                "", //  variableVal,
                "", //  sourceEventId,
                "", //  sourceEventName,
                "", //  voivodship,
                "", //  district,
                "", //  platetype,
                "", //  plateId,
                "" //  allowance
    );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Cause=Intrusion / EVENT : Cause=Null ", !result);
}
void MacroExpressionTest::at_variable_test1() {
    std::wstring conditionsCompiled = L"<\">@1073741825<\"/> =  <\">1<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                    "1",//  int,
                    "", //  name,
                    "", //  conditionsJson,
                    conditionsCompiled, //  conditionCompiled,
                    "", //  actionType,
                    "", //  actionOut,
                    "", //  action,
                    "", //  actionType2,
                    "", //  actionOut2,
                    "", //  action2,
                    "", //  actionType3,
                    "", //  actionOut3,
                    "", //  action3,
                    "", //  autoExecute,
                    "", //  autoExecuteCmd,
                    ""  //  message
            );

    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                    "1", //  monitorId,
                    "", //  name,
                    "Null", //  cause,
                    "", //  userCause,
                    "", //  startDateTime,
                    "", //  endDateTime,
                    "", //  notes,
                    "", //  recognition,
                    "", //  person,
                    "", //  faceType,
                    "", //  lprDirection,
                    "", //  variableId,
                    "", //  variableVal,
                    "", //  sourceEventId,
                    "", //  sourceEventName,
                    "", //  voivodship,
                    "", //  district,
                    "", //  platetype,
                    "", //  plateId,
                    "" //  allowance
            );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);
    params.setParam(L"@1073741825", L"1");

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : @1073741825=1 / EVENT : @1073741825=1 ", result);
}
void MacroExpressionTest::at_variable_test2() {
    std::wstring conditionsCompiled = L"<\">@1073741825<\"/> =  <\">1<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                    "1",//  int,
                    "", //  name,
                    "", //  conditionsJson,
                    conditionsCompiled, //  conditionCompiled,
                    "", //  actionType,
                    "", //  actionOut,
                    "", //  action,
                    "", //  actionType2,
                    "", //  actionOut2,
                    "", //  action2,
                    "", //  actionType3,
                    "", //  actionOut3,
                    "", //  action3,
                    "", //  autoExecute,
                    "", //  autoExecuteCmd,
                    ""  //  message
            );

    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                    "1", //  monitorId,
                    "", //  name,
                    "Null", //  cause,
                    "", //  userCause,
                    "", //  startDateTime,
                    "", //  endDateTime,
                    "", //  notes,
                    "", //  recognition,
                    "", //  person,
                    "", //  faceType,
                    "", //  lprDirection,
                    "", //  variableId,
                    "", //  variableVal,
                    "", //  sourceEventId,
                    "", //  sourceEventName,
                    "", //  voivodship,
                    "", //  district,
                    "", //  platetype,
                    "", //  plateId,
                    "" //  allowance
            );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);
    params.setParam(L"@1073741825", L"0");

    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : @1073741825=1 / EVENT : @1073741825=0 ", !result);
}

void MacroExpressionTest::at_variable_test3() {
    std::wstring conditionsCompiled = L"<\">@1073741825<\"/> =  <\">1<\"/>  and  <\">@1073741826<\"/> =  <\">1<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                    "1",//  int,
                    "", //  name,
                    "", //  conditionsJson,
                    conditionsCompiled, //  conditionCompiled,
                    "", //  actionType,
                    "", //  actionOut,
                    "", //  action,
                    "", //  actionType2,
                    "", //  actionOut2,
                    "", //  action2,
                    "", //  actionType3,
                    "", //  actionOut3,
                    "", //  action3,
                    "", //  autoExecute,
                    "", //  autoExecuteCmd,
                    ""  //  message
            );

    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                    "1", //  monitorId,
                    "", //  name,
                    "Null", //  cause,
                    "", //  userCause,
                    "", //  startDateTime,
                    "", //  endDateTime,
                    "", //  notes,
                    "", //  recognition,
                    "", //  person,
                    "", //  faceType,
                    "", //  lprDirection,
                    "", //  variableId,
                    "", //  variableVal,
                    "", //  sourceEventId,
                    "", //  sourceEventName,
                    "", //  voivodship,
                    "", //  district,
                    "", //  platetype,
                    "", //  plateId,
                    "" //  allowance
            );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);
    params.setParam(L"@1073741825", L"1");
    params.setParam(L"@1073741826", L"1");


    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Cause=Intrusion / EVENT : Cause=Null ", result);
}
void MacroExpressionTest::at_variable_test4() {
    std::wstring conditionsCompiled = L"<\">@1073741825<\"/> =  <\">1<\"/>  and  <\">@1073741826<\"/> !=  <\">1<\"/>";
    pjpl::model::EventMacroRecord::ptr eventMacro
            = std::make_shared<pjpl::model::EventMacroRecord>(
                    "1",//  int,
                    "", //  name,
                    "", //  conditionsJson,
                    conditionsCompiled, //  conditionCompiled,
                    "", //  actionType,
                    "", //  actionOut,
                    "", //  action,
                    "", //  actionType2,
                    "", //  actionOut2,
                    "", //  action2,
                    "", //  actionType3,
                    "", //  actionOut3,
                    "", //  action3,
                    "", //  autoExecute,
                    "", //  autoExecuteCmd,
                    ""  //  message
            );

    pjpl::model::EventToServeRecord::ptr eventToServe
            = std::make_shared<pjpl::model::EventToServeRecord>(
                    "1", //  monitorId,
                    "", //  name,
                    "Null", //  cause,
                    "", //  userCause,
                    "", //  startDateTime,
                    "", //  endDateTime,
                    "", //  notes,
                    "", //  recognition,
                    "", //  person,
                    "", //  faceType,
                    "", //  lprDirection,
                    "", //  variableId,
                    "", //  variableVal,
                    "", //  sourceEventId,
                    "", //  sourceEventName,
                    "", //  voivodship,
                    "", //  district,
                    "", //  platetype,
                    "", //  plateId,
                    "" //  allowance
            );

    pjpl::model::ParamsForFilter params(pjpl::db::DB::i()->getDriver());
    params.reload(eventToServe, eventMacro);
    params.setParam(L"@1073741825", L"1");
    params.setParam(L"@1073741826", L"0");


    pjpl::MacroExpression me;
    bool result;

    me.setExpression(eventMacro->getConditionsCompiled());
    me.logic(params.getParams(), params.getInParams(), eventToServe, result);

    CPPUNIT_ASSERT_MESSAGE("MACRO : Cause=Intrusion / EVENT : Cause=Null ", result);
}

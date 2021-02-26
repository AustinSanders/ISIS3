#include "CubeStretch.h"
#include "StretchBlob.h"
#include "IException.h"
#include "Cube.h"
#include "TestUtilities.h"
#include "Fixtures.h"

#include <QString>
#include <QDebug>

#include <gtest/gtest.h>
#include "gmock/gmock.h"

using namespace Isis;

TEST(StretchBlob, Constructors) {
  // Default
  StretchBlob stretchBlob;

  // Set Name
  StretchBlob nameStretchBlob("name");

  // Set Stretch
  CubeStretch cubeStretch("TestStretch", "testType", 2);
  StretchBlob stretchStretchBlob(cubeStretch);
  StretchBlob stretchFromBlob(*(stretchStretchBlob.toBlob()));

  // Test retrieval of cubeStretch from StretchBlob
  CubeStretch retrievedStretch = stretchStretchBlob.getStretch();

  EXPECT_STREQ(stretchBlob.getStretch().getName().toLatin1().data(), "DefaultStretch");
  EXPECT_STREQ(stretchBlob.getStretch().getType().toLatin1().data(), "Default");

  EXPECT_STREQ(nameStretchBlob.getStretch().getName().toLatin1().data(), "name");
  EXPECT_STREQ(nameStretchBlob.getStretch().getType().toLatin1().data(), "Default");

  EXPECT_STREQ(stretchStretchBlob.getStretch().getName().toLatin1().data(), "TestStretch");
  EXPECT_STREQ(stretchStretchBlob.getStretch().getType().toLatin1().data(), "testType");

  EXPECT_STREQ(retrievedStretch.getName().toLatin1().data(), cubeStretch.getName().toLatin1().data());
  EXPECT_STREQ(retrievedStretch.getType().toLatin1().data(), cubeStretch.getType().toLatin1().data());

  EXPECT_STREQ(stretchFromBlob.getStretch().getType().toLatin1().data(), cubeStretch.getType().toLatin1().data());
  EXPECT_EQ(retrievedStretch.getBandNumber(), cubeStretch.getBandNumber());
};


TEST_F(DefaultCube, StretchBlobWriteRead) {
  // Set up Stretch to write
  QString stretchName = "TestStretch";
  CubeStretch cubeStretch(stretchName, "testType", 2);

  // add pair(s)
  cubeStretch.AddPair(0.0, 1.0);
  cubeStretch.AddPair(0.25, 50.0);
  cubeStretch.AddPair(1.0, 100.0);
  Isis::StretchBlob stretchBlob(cubeStretch);

  // Write to Cube
  testCube->write(*(stretchBlob.toBlob()));
  testCube->reopen("rw");
  
  // Set up stretch and blob to restore to
  StretchBlob restoreBlob = testCube->readStretchBlob(stretchName);
  CubeStretch restoredStretch = stretchBlob.getStretch();
  EXPECT_TRUE(restoredStretch == cubeStretch);
};

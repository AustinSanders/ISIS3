#ifndef Mock_h
#define Mock_h

#include "Process.h"
#include "Transform.h"
#include "Interpolator.h"
#include "gmock/gmock.h"
#include "ProcessRubberSheet.h"
#include "Cube.h"

using namespace Isis;

class MockProcessRubberSheet : public ProcessRubberSheet {
public:
  MOCK_METHOD(void, StartProcess, (Transform &trans, Interpolator &interp), (override));
  MOCK_METHOD(Cube*, SetOutputCube, (const QString &fname,
                                     const Isis::CubeAttributeOutput &att,
                                     const int ns, const int nl,
                                     const int nb), (override));
  MOCK_METHOD(void, SetInputCube, (Cube *inCube), (override));
  MOCK_METHOD(void, processPatchTransform, (Transform &trans, Interpolator &interp), (override));
  MOCK_METHOD(void, setPatchParameters, (int startSample, int startLine, int samples,
                                         int lines, int sampleIncrement, int lineIncrement), (override));
  MOCK_METHOD(void, forceTile, (double Samp, double Line));
  MOCK_METHOD(void, SetTiling, (long long start, long long end));
  MOCK_METHOD(void, EndProcess, (), (override));
  MOCK_METHOD(void, BandChange, (void (*funct)(const int band)), (override));
};


#endif

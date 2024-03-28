#include <cmath>

#include <gtest/gtest.h>
#include <../include/vector1.h>

TEST(ConstructorTests, ConstructorWithDimension_WhenCalled_CreatesVectorWithZeros)
{
  size_t dimension = 10;
  Vector v = Vector(dimension);
  std::vector<double> coordinates;
  for (size_t i = 0; i < dimension; ++i)
    coordinates.push_back(0.0);

  EXPECT_EQ(v.getDimension(), dimension);
  EXPECT_EQ(v.getCoordinates(), coordinates);
}

TEST(ConstructorTests, ConstructorWithInitializerList_WhenCalled_CreatesVectorAndFillByValues)
{
  Vector v = {1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector<double> coordinates;
  for (size_t i = 1; i <= 5; ++i)
    coordinates.push_back((double)i);

  EXPECT_EQ(v.getDimension(), 5);
  EXPECT_EQ(v.getCoordinates(), coordinates);
}

TEST(ConstructorTests, ConstructorWithVector_WhenCalled_CreatesVectorAndFillByValues)
{
  std::vector<double> coordinates;
  for (size_t i = 1; i <= 5; ++i)
    coordinates.push_back((double)i);
  Vector v = Vector(coordinates);

  EXPECT_EQ(v.getDimension(), coordinates.size());
  EXPECT_EQ(v.getCoordinates(), coordinates);
}

TEST(ConstructorTests, CopyConstructor_WhenCalled_CreatesVectorAndCopyFields)
{
  Vector v1 = {1.0, 2.0, 3.0, 4.0, 5.0};
  Vector v2 = Vector(v1);

  EXPECT_EQ(v1.getDimension(), v2.getDimension());
  EXPECT_EQ(v1.getCoordinates(), v2.getCoordinates());
}

TEST(AssignmentTests, AssignmentOperator_WhenCalled_CopiesFields)
{
  Vector v1 = {1.0, 2.0, 3.0, 4.0, 5.0};
  Vector v2 = Vector(10);
  v2 = v1;

  EXPECT_EQ(v1.getDimension(), v2.getDimension());
  EXPECT_EQ(v1.getCoordinates(), v2.getCoordinates());
}

TEST(AssignmentTests, AssignmentOperator_AssignsItself_ReturnsItself)
{
  std::vector<double> valuesVector;
  for (size_t i = 0; i < 5; ++i) valuesVector.push_back((double) (i+1));
  Vector v1 = {1.0, 2.0, 3.0, 4.0, 5.0};
  v1 = v1;

  EXPECT_EQ(v1.getDimension(), 5);
  EXPECT_EQ(v1.getCoordinates(), valuesVector);
}

TEST(EuclideanNormtests, EuclideanNormOperator_GetsEuclideanNorm_ReturnsDoubleValue) {
  Vector v = {1.0, 2.0, 3.0, 4.0};
  double norm = sqrt(30);
  double normValue = v.getEuclideanNorm();

  EXPECT_EQ(normValue, norm);
}

TEST(EuclideanNormtests, EuclideanNormOperator_GetsEuclideanNormOfZeroVector_ReturnsZero) {
  Vector v = Vector(10);
  double normValue = v.getEuclideanNorm();

  EXPECT_EQ(normValue, 0.0);
}

TEST(OutputTests, OutputOperator_PrintVector_ReturnsStringWithValuesInBrackets1)
{
  Vector v = {1.0, 2.0, 3.0};
  std::string stringVector = "(1, 2, 3)";
  std::stringstream buffer;
  buffer << v;

  EXPECT_EQ(buffer.str(), stringVector);
}

TEST(OutputTests, OutputOperator_PrintVector_ReturnsStringWithValuesInBrackets2)
{
  Vector v = {1.15, 2.8294, 3.4, 4.00};
  std::string stringVector = "(1.15, 2.8294, 3.4, 4)";
  std::stringstream buffer;
  buffer << v;

  EXPECT_EQ(buffer.str(), stringVector);
}

TEST(ComparationTests, IsEqualOperator_ComparesTheSameVectors_ReturnsTrue)
{
  Vector v1 = {1.0, 2.0, 3.0};
  Vector v2 = {1.0, 2.0, 3.0};

  EXPECT_TRUE(v1 == v2);
}

TEST(ComparationTests, IsEqualOperator_ComparesDifferentVectors_ReturnsFalse)
{
  Vector v1 = {1.0, 2.0};
  Vector v2 = {1.0, 2.0, 3.0};

  EXPECT_FALSE(v1 == v2);
}

TEST(ComparationTests, IsNotEqualOperator_ComparesTheSameVectors_ReturnsFalse)
{
  Vector v1 = {1.0, 2.0, 3.0};
  Vector v2 = {1.0, 2.0, 3.0};

  EXPECT_FALSE(v1 != v2);
}

TEST(ComparationTests, IsNotEqualOperator_ComparesDifferentVectors_ReturnsTrue)
{
  Vector v1 = {1.0, 2.0};
  Vector v2 = {1.0, 2.0, 3.0};

  EXPECT_TRUE(v1 != v2);
}

TEST(SumTests, SumOperator_SumsTwoVectors_ReturnsNewVectorWithSumValue)
{
  Vector v1 = {-1.0, 1.0, 3.5, 8.5, 6.0};
  Vector v2 = {5.0, 4.8, -2.0, 7.5, 1.0};
  Vector v3 = v1 + v2;
  std::vector<double> sumVector;
  for (size_t i = 0; i < v1.getDimension(); ++i)
  {
    sumVector.push_back(v1.getCoordinates()[i] + v2.getCoordinates()[i]);
  }

  EXPECT_EQ(v3.getCoordinates(), sumVector);
  EXPECT_EQ(v3.getDimension(), v1.getDimension());
  EXPECT_EQ(v3.getDimension(), v2.getDimension());
}

TEST(SumTests, SumOperator_SumsTwoZeroVectors_ReturnsNewZeroVector)
{
  Vector v1 = Vector(5);
  Vector v2 = Vector(5);
  Vector v3 = v1 + v2;
  std::vector<double> sumVector;
  for (size_t i = 0; i < v1.getDimension(); ++i)
  {
    sumVector.push_back(0.0);
  }

  EXPECT_EQ(v3.getCoordinates(), sumVector);
}

TEST(SumTests, SumOperator_SumsTwoVectorsWithDifferentDimensions_ThrowsException)
{
  Vector v1 = Vector(5);
  Vector v2 = Vector(4);

  ASSERT_THROW(v1 + v2, std::invalid_argument);
}

TEST(SubTests, SubOperator_SubsTwoVectors_ReturnsNewVectorWithSubValue)
{
  Vector v1 = {-1.0, 1.0, 3.5, 8.5, 6.0};
  Vector v2 = {5.0, 4.8, -2.0, 7.5, 1.0};
  Vector v3 = v1 - v2;
  std::vector<double> sumVector;
  for (size_t i = 0; i < v1.getDimension(); ++i)
  {
    sumVector.push_back(v1.getCoordinates()[i] - v2.getCoordinates()[i]);
  }

  EXPECT_EQ(v3.getCoordinates(), sumVector);
  EXPECT_EQ(v3.getDimension(), v1.getDimension());
  EXPECT_EQ(v3.getDimension(), v2.getDimension());
}

TEST(SubTests, SubOperator_SubsTwoZeroVectors_ReturnsNewZeroVector)
{
  Vector v1 = Vector(5);
  Vector v2 = Vector(5);
  Vector v3 = v1 - v2;
  std::vector<double> subVector;
  for (size_t i = 0; i < v1.getDimension(); ++i)
  {
    subVector.push_back(0.0);
  }

  EXPECT_EQ(v3.getCoordinates(), subVector);
}

TEST(SubTests, SubOperator_SumsTwoVectorsWithDifferentDimensions_ThrowsException)
{
  Vector v1 = Vector(5);
  Vector v2 = Vector(4);

  ASSERT_THROW(v1 - v2, std::invalid_argument);
}

TEST(ScalarProductTests, ScalarProductOperator_GetsScalarProductOfTwoZeroVectors_ReturnsZero) {
  Vector v1 = Vector(10);
  Vector v2 = Vector(10);
  double vectorsScalarProduct = scalarProduct(v1, v2);

  EXPECT_EQ(vectorsScalarProduct, 0.0);
}

TEST(ScalarProductTests, ScalarProductOperator_GetsScalarProductOfTwoVectors_ReturnsDoubleValue) {
  Vector v1 = {1.0, 2.0, 3.0, 4.0};
  Vector v2 = {1.0, 3.0, 5.0, 7.0};
  double vectorsScalarProduct = scalarProduct(v1, v2);

  EXPECT_EQ(vectorsScalarProduct, 50.0);
}

TEST(ScalarProductTests, ScalarProductOperator_GetsScalarProductOfVectorsWithDifferentDimensions_ThrowsException) {
  Vector v1 = Vector(9);
  Vector v2 = Vector(10);

  ASSERT_THROW(scalarProduct(v1, v2), std::invalid_argument);
}

TEST(VectorProductTests, VectorProductOperator_GetsVectorVectorProductOfTwoZeroVectors_ReturnsZeroVector) {
  Vector v1 = Vector(3);
  Vector v2 = Vector(3);
  Vector v3 = vectorProduct(v1, v2);
  Vector zeroVector = Vector(3);

  EXPECT_EQ(v3, zeroVector);
}

TEST(VectorProductTests, VectorProductOperator_GetsVectorProductOfTwoVectors_ReturnsNewVector) {
  Vector v1 = {1.0, 2.0, -1.0};
  Vector v2 = {4.0, 3.0, -8.0};
  Vector v3 = vectorProduct(v1, v2);
  Vector resultVector = {-13.0, 4.0, -5.0};

  EXPECT_EQ(v3, resultVector);
}

TEST(VectorProductTests, VectorProductOperator_GetsVectorProductOfNotThreeDimensionalVectors_ThrowsException) {
  Vector v1 = Vector(4);
  Vector v2 = Vector(4);

  ASSERT_THROW(vectorProduct(v1, v2), std::invalid_argument);
}

TEST(VectorProductTests, VectorProductOperator_GetsVectorProductOfVectorsWithDifferentDimensions_ThrowsException1) {
  Vector v1 = Vector(3);
  Vector v2 = Vector(2);

  ASSERT_THROW(vectorProduct(v1, v2), std::invalid_argument);
}

TEST(VectorProductTests, VectorProductOperator_GetsVectorProductOfVectorsWithDifferentDimensions_ThrowsException2) {
  Vector v1 = Vector(2);
  Vector v2 = Vector(3);

  ASSERT_THROW(vectorProduct(v1, v2), std::invalid_argument);
}

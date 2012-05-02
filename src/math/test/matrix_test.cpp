// * This file is part of the COLOBOT source code
// * Copyright (C) 2012, Polish Portal of Colobot (PPC)
// *
// * This program is free software: you can redistribute it and/or modify
// * it under the terms of the GNU General Public License as published by
// * the Free Software Foundation, either version 3 of the License, or
// * (at your option) any later version.
// *
// * This program is distributed in the hope that it will be useful,
// * but WITHOUT ANY WARRANTY; without even the implied warranty of
// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// * GNU General Public License for more details.
// *
// * You should have received a copy of the GNU General Public License
// * along with this program. If not, see  http://www.gnu.org/licenses/.

// math/test/matrix_test.cpp

/* Unit tests for Matrix struct

   Test data was randomly generated and the expected results
   calculated using GNU Octave.

 */

#include "../func.h"
#include "../matrix.h"

#include <cstdio>

using namespace std;

const float TEST_TOLERANCE = 1e-6;

int TestTranspose()
{
  const Math::Matrix mat(
    (float[4][4])
    {
      { -0.07011674491203920,  1.26145596067429810,  2.09476603598066902,  0.35560176915570696 },
      { -1.34075615966224704,  1.17988499016709314,  0.00601713429241016, -0.75213676977972566 },
      {  0.59186722295223981,  0.88089224074765293,  0.70994467464257294,  0.36730385425340212 },
      { -0.95649396555068111,  0.75912182022565566,  1.34883305778387186, -1.34957997578168754 }
    }
  );

  const Math::Matrix expectedTranspose(
    (float[4][4])
    {
      { -0.07011674491203920, -1.34075615966224704,  0.59186722295223981, -0.95649396555068111 },
      {  1.26145596067429810,  1.17988499016709314,  0.88089224074765293,  0.75912182022565566 },
      {  2.09476603598066902,  0.00601713429241016,  0.70994467464257294,  1.34883305778387186 },
      {  0.35560176915570696, -0.75213676977972566,  0.36730385425340212, -1.34957997578168754 }
    }
  );

  Math::Matrix transpose = Math::Transpose(mat);

  if (! Math::MatricesEqual(transpose, expectedTranspose, TEST_TOLERANCE))
  {
    fprintf(stderr, "Transpose mismatch!\n");
    return __LINE__;
  }

  return 0;
}

int TestCofactor()
{
  const Math::Matrix mat1(
    (float[4][4])
    {
      {  0.610630320796245,  1.059932357918312, -1.581674311378210,  1.782214448453331 },
      {  0.191028848211526, -0.813898708757524,  1.516114203870644,  0.395202639476002 },
      {  0.335142750345279, -0.346586619596529,  0.545382042472336, -0.879268918923072 },
      {  1.417588151657198,  1.450841789070141,  0.219080104196171,  0.378724047481655 }
    }
  );

  const Math::Matrix expectedCofactors1(
    (float[4][4])
    {
      { -2.402679369186782,  2.282452509293019,  1.722732204057644, -0.746939701104385 },
      { -0.687677756877654,  1.168949180331164, -0.985354966837796, -1.334071111592705 },
      { -5.115621958424845,  4.229724770159009,  2.529000630782808,  1.481632618355891 },
      {  0.147480897398694, -2.140677680337111, -1.207189492265546,  0.151236920408051 }
    }
  );

  for (int r = 0; r < 4; ++r)
  {
    for (int c = 0; c < 4; ++c)
    {
      float ret = mat1.Cofactor(r, c);
      float exp = expectedCofactors1.m[4*c+r];
      if (! Math::IsEqual(ret, exp, TEST_TOLERANCE))
      {
        fprintf(stderr, "Cofactors 1 mismatch!\n");
        fprintf(stderr, "r=%d, c=%d, %f (returned) != %f (expected)\n", r, c, ret, exp);
        return __LINE__;
      }
    }
  }

  const Math::Matrix mat2(
    (float[4][4])
    {
      {  0.9845099464982393, -0.9091233416532389, -0.6272243714245945,  0.4645001858944354 },
      { -0.1333308471483736,  0.9128181433725897, -1.0937461393836190,  0.3180936795928376 },
      { -0.0654324396846289,  0.1014641705415945,  1.5107709042683430, -0.0240560430414690 },
      {  0.0179638644093347, -1.0695585982782767, -0.1741250853101032,  1.0803106709464336 }
    }
  );

  const Math::Matrix expectedCofactors2(
    (float[4][4])
    {
      {  2.0861102207614466,  0.2989010779528912,  0.0746276150537432,  0.2732659822656097 },
      {  0.6850002886584565,  1.5513169659641379, -0.0503743176545917,  1.5163672441575642 },
      {  1.2385556680997216,  1.1827709562505695,  1.2282813085138962,  1.3483789679871401 },
      { -1.0710790241539783, -0.5589604503588883,  0.0100959837872308,  1.1897872684455839 }
    }
  );


  for (int r = 0; r < 4; ++r)
  {
    for (int c = 0; c < 4; ++c)
    {
      float ret = mat2.Cofactor(r, c);
      float exp = expectedCofactors2.m[4*c+r];
      if (! Math::IsEqual(ret, exp, TEST_TOLERANCE))
      {
        fprintf(stderr, "Cofactors 2 mismatch!\n");
        fprintf(stderr, "r=%d, c=%d, %f (returned) != %f (expected)\n", r, c, ret, exp);
        return __LINE__;
      }
    }
  }

  return 0;
}

int TestDet()
{
  const Math::Matrix mat1(
    (float[4][4])
    {
      { -0.95880162984708284,  0.24004047608997131, -0.78172309932665407, -0.11604124457222834 },
      { -0.36230592086261376, -0.75778166876017261,  0.33041059404631740, -1.06001391941094836 },
      {  0.00260215210936187,  1.27485610196385113, -0.26149859846418033, -0.59669701186364876 },
      {  0.36899429848485432,  3.01720896813933104,  2.10311476609438719, -1.68627076626448269 }
    }
  );

  const float expectedDet1 = 4.07415413729671;

  float ret1 = mat1.Det();
  if (! Math::IsEqual(ret1, expectedDet1, TEST_TOLERANCE))
  {
    fprintf(stderr, "Det mismatch!\n");
    fprintf(stderr, "%f (returned) != %f (expected)\n", ret1, expectedDet1);
    return __LINE__;
  }

  const Math::Matrix mat2(
    (float[4][4])
    {
      { -1.0860073221346871,  0.9150354098189495, -0.2723201933559999,  0.2922832160271507 },
      { -1.0248331304801788, -2.5081237461125205, -1.0277123574586633, -0.2254690663329798 },
      { -1.4227635282899367, -0.0403846809122684,  0.9216148477171653,  1.2517067488015878 },
      { -0.1160254467152022,  0.8270675274393656,  1.0327218739781614, -0.3674886870220400 }
    }
  );

  const float expectedDet2 = -6.35122307880942;

  float ret2 = mat2.Det();
  if (! Math::IsEqual(ret2, expectedDet2, TEST_TOLERANCE))
  {
    fprintf(stderr, "Det mismatch!\n");
    fprintf(stderr, "%f (returned) != %f (expected)\n", ret2, expectedDet2);
    return __LINE__;
  }

  return 0;
}

int TestInverse()
{
  const Math::Matrix mat1(
    (float[4][4])
    {
      { -2.2829352811514658, -0.9103222363187888,  0.2792976509411680, -0.7984393573193174 },
      {  2.4823665798689589, -0.0599056759070980,  0.3832364352926366, -1.6404257204372739 },
      { -0.3841952272526398, -0.8377700696457873, -0.3416328338427138,  1.1746577275723329 },
      {  0.1746031241954947, -0.4952532117949962,  0.2155084379835037, -1.6586460437329220 }
    }
  );

  const Math::Matrix expectedInverse1(
    (float[4][4])
    {
      { -0.119472603171041,  0.331675963276297,  0.187516809009720, -0.137720814290806 },
      { -0.387591686166085, -0.487284946727583, -0.798527541290274,  0.102991635972060 },
      {  2.601905603425902,  2.606899016264679, -0.528006148839176, -4.204703326522837 },
      {  0.441220327151392,  0.519128136207318,  0.189567009205522, -1.194469716136194 }
    }
  );

  Math::Matrix inverse1 = mat1.Inverse();

  if (! Math::MatricesEqual(inverse1, expectedInverse1, TEST_TOLERANCE))
  {
    fprintf(stderr, "Inverse 1 mismatch!\n");
    return __LINE__;
  }

  const Math::Matrix mat2(
    (float[4][4])
    {
      { -0.05464332404298505, -0.64357755258235749, -0.13017671677619302, -0.56742332785888006 },
      {  0.29048383600458222, -0.91517047043724875,  0.84517524415561684,  0.51628195547960565 },
      {  0.00946488004480186, -0.89077382212689293,  0.73565573766341397, -0.15932513521840930 },
      { -1.01244718912499132, -0.27840911963972276, -0.39189681211309862,  1.18315064340192055 }
    }
  );

  const Math::Matrix expectedInverse2(
    (float[4][4])
    {
      {  0.771302711132012,  1.587542278361995, -2.003075114445104, -0.592574156227379 },
      { -1.208929259769431, -0.786598967848473,  0.607335305808052, -0.154759693303324 },
      { -1.500037668208218, -0.774300278997914,  1.917800427261255, -0.123268572651291 },
      { -0.121314770937944,  0.916925149209746, -0.935924950785014,  0.260875394250671 }
    }
  );

  Math::Matrix inverse2 = mat2.Inverse();

  if (! Math::MatricesEqual(inverse2, expectedInverse2, TEST_TOLERANCE))
  {
    fprintf(stderr, "Inverse 2 mismatch!\n");
    return __LINE__;
  }

  return 0;
}

int TestMultiply()
{
  const Math::Matrix mat1A(
    (float[4][4])
    {
      {  0.6561727049162027, -1.4180263627131411, -0.8271026046117423,  2.3919331748512578 },
      { -0.6035665535146352,  0.0150827348790615, -0.7090794192822540,  0.9057604704594814 },
      { -0.9871045001223655, -0.4980646811455065,  0.3806177002298990,  0.1520583649240934 },
      { -0.2721911170792712,  0.7627928194552067, -0.1504091336784158,  0.9747545351840121 }
    }
  );

  const Math::Matrix mat1B(
    (float[4][4])
    {
      { -0.2643735892448818, -0.7542994492819621,  0.6082322350568750,  0.0581733424861419 },
      {  1.0293246070431237,  0.1979285388251341, -0.2932031385332818,  0.8838407179018929 },
      {  0.3448687251553114,  0.5031654871245456,  0.7554693012922442, -0.4845315903845708 },
      { -1.8662838497278593, -0.7843850624747805,  0.1389026096476257, -1.3686415408300689 }
    }
  );

  const Math::Matrix expectedMultiply1(
    (float[4][4])
    {
      { -6.382352236417988, -3.067984733682130,  0.522270304251466, -4.088079444498280 },
      { -1.759853366848825, -0.608994052024491, -0.781406179437379, -0.917870775786188 },
      { -0.404226802169062,  0.718232546720114, -0.145688356880835, -0.890167707987175 },
      { -1.013918490922430, -0.483971504099758, -0.367442194643757, -0.602858486133615 }
    }
  );

  Math::Matrix multiply1 = Math::MultiplyMatrices(mat1A, mat1B);
  if (! Math::MatricesEqual(multiply1, expectedMultiply1, TEST_TOLERANCE ) )
  {
    fprintf(stderr, "Multiply 1 mismath!\n");
    return __LINE__;
  }

  const Math::Matrix mat2A(
    (float[4][4])
    {
      {  0.8697203025776754,  2.1259475710644935,  1.7856691009707812, -2.1563963348328126 },
      {  1.5888074489288735, -0.0794849733953615,  0.7307782768677457,  0.7943129159612630 },
      {  0.2859761537233830, -0.6231231890384962, -0.0496743172880377, -0.8137857518646087 },
      {  1.2670547229512983, -0.5305171374831831, -0.4987412674062375, -1.1257327113869595 }
    }
  );

  const Math::Matrix mat2B(
    (float[4][4])
    {
      {  1.1321105701165317,  0.1759563504574463, -2.0675778912000418,  1.4840339814245538 },
      { -1.5117280888829916, -0.0933013188828093, -0.2079262944351640,  0.9575727579539316 },
      {  0.3615378398970173,  1.2465163589027248,  1.1326150997082589,  0.9921208694352303 },
      { -0.7357104529373861, -0.4774022005969588, -0.2118739096676499,  1.1427567093270703 }
    }
  );

  const Math::Matrix expectedMultiply2(
    (float[4][4])
    {
      {  0.00283516267056338,  3.21001319965989307,  0.23910503934370686,  2.63380716363006107 },
      {  1.59868505822469742,  0.81869715594617765, -2.60905981088293570,  3.91445839239110294 },
      {  1.84650099286297942,  0.43504079532852930, -0.34555619012424243, -1.15152951542451487 },
      {  2.88434318563174585,  0.18818239851585700, -2.83579436909308980, -0.40890672198610400 }
    }
  );

  Math::Matrix multiply2 = Math::MultiplyMatrices(mat2A, mat2B);
  if (! Math::MatricesEqual(multiply2, expectedMultiply2, TEST_TOLERANCE ) )
  {
    fprintf(stderr, "Multiply 2 mismath!\n");
    return __LINE__;
  }

  return 0;
}

int TestMultiplyVector()
{
  const Math::Matrix mat1(
    (float[4][4])
    {
      {  0.0536517635602049,  0.1350203249258820, -1.4709867280474975,  1.4199163191255975 },
      {  0.4308040094214364,  0.6860887768493787,  0.0555235810428098,  0.0245232625281863 },
      { -0.9570012049134703,  1.4008557175488343,  1.0277555933198543,  1.2311131809078903 },
      {  1.5609168701538376, -0.4917648784647429,  1.3748498152379420,  0.2479075063284996 }
    }
  );

  const Math::Vector vec1(0.587443623396385, 0.653347527302101, -0.434049355720428);

  const Math::Vector expectedMultiply1(8.82505163446795, 2.84325886975415, 4.61111014687784);

  Math::Vector multiply1 = Math::MatrixVectorMultiply(mat1, vec1);
  if (! Math::VectorsEqual(multiply1, expectedMultiply1, TEST_TOLERANCE ) )
  {
    fprintf(stderr, "Multiply vector 1 mismath!\n");
    return __LINE__;
  }

  const Math::Matrix mat2(
    (float[4][4])
    {
      {  1.2078126667092564,  0.5230257362392928, -0.7623036312496848, -1.4192273892400153 },
      {  0.7165407622837081,  1.3746282484390115, -0.8382279333943382,  0.8248340530209490 },
      { -0.9595506321366957, -0.0169226311095793, -0.7271125620609374, -1.5540250647342428 },
      {  1.2788946935793131,  0.1516426145850322,  1.2115324484930112, -0.1584402989052367 }
    }
  );

  const Math::Vector vec2(-0.7159607709627414, -0.3163937238507886, 0.0290730716146861);

  const Math::Vector expectedMultiply2(2.274144199387390, 0.135691892790685, 0.812276027335184);

  Math::Vector multiply2 = Math::MatrixVectorMultiply(mat2, vec2);
  if (! Math::VectorsEqual(multiply2, expectedMultiply2, TEST_TOLERANCE ) )
  {
    fprintf(stderr, "Multiply vector 2 mismath!\n");
    return __LINE__;
  }

  return 0;
}

int main()
{
  // Functions to test
  int (*TESTS[])() =
  {
    TestTranspose,
    TestCofactor,
    TestDet,
    TestInverse,
    TestMultiply,
    TestMultiplyVector
  };
  const int TESTS_SIZE = sizeof(TESTS) / sizeof(*TESTS);

  int result = 0;
  for (int i = 0; i < TESTS_SIZE; ++i)
  {
    result = TESTS[i]();
    if (result != 0)
      return result;
  }

  fprintf(stderr, "All tests successful\n");

  return 0;
}


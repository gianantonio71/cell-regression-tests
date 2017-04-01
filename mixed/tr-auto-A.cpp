#include "common.h"

using generated::TrAutoA;


void run_TrAutoA_tests(const char *file, bool set_state) {
  TrAutoA test_db;

  if (file != NULL) {
    char buffer[65536];

    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
      printf("Cannot open file %s\n", file);
      return;
    }
    int count = fread(buffer, 1, 32768, fp);
    buffer[count] = '\0';
    fclose(fp);

    if (set_state)
      test_db.set_state(buffer);
    else
      test_db.execute(buffer);
  }
  else {
    test_db.execute("my_msg");
  }

  bool bool_output = test_db.get_A_bool_var();
  long long int_output = test_db.get_An_int_var();
  double float_output = test_db.get_A_float_var();
  const char *symb_output = test_db.get_A_symb_var();

  string str = test_db.get_A_string_var();
  vector<bool> bools = test_db.get_A_bool_seq_var();
  vector<long long> llongs = test_db.get_An_int_seq_var();
  vector<double> doubles = test_db.get_A_float_seq_var();

  printf("%s - %lld - %f - %s - %s\n", bool_output ? "true" : "false", int_output, float_output, symb_output, str.c_str());
  for (int i=0 ; i < bools.size() ; i++)
    printf("%d ", (int) bools[i]);
  printf("\n");
  for (int i=0 ; i < llongs.size() ; i++)
    printf("%lld ", llongs[i]);
  printf("\n");
  for (int i=0 ; i < doubles.size() ; i++)
    printf("%f ", doubles[i]);
  printf("\n\n");

  tuple<double, string, vector<long long> > tuple_3A = test_db.get_A_tuple_var();
  double f0 = get<0>(tuple_3A);
  str = get<1>(tuple_3A);
  llongs = get<2>(tuple_3A);

  printf("%f - %s -", f0, str.c_str());
  for (int i=0 ; i < llongs.size() ; i++)
    printf(" %lld", llongs[i]);
  printf("\n");

  unique_ptr<Value> val = test_db.get_A_date_rec_var();
  int day = val->lookup("day")->as_int();
  int month = val->lookup("month")->as_int();
  int year = val->lookup("year")->as_int();
  printf("%02d/%02d/%d\n\n", day, month, year);

  vector<unique_ptr<Value> > vals = test_db.get_A_point_seq_var();
  for (int i=0 ; i < vals.size() ; i++)
    printf("%s ", vals[i]->printed().c_str());
  putchar('\n');

  int x = test_db.get_A_point_var()->lookup("x")->as_int();
  int y = test_db.get_A_point_var()->lookup("y")->as_int();
  printf("point(x: %d, y: %d)\n", x, y);

  tuple<long long, long long, long long> tuple_3B = test_db.get_A_date_var();
  day = get<0>(tuple_3B);
  month = get<1>(tuple_3B);
  year = get<2>(tuple_3B);
  printf("date(%d, %d, %d)\n", day, month, year);

  int time_span = test_db.get_A_time_span_var();
  printf("msecs(%d)\n", time_span);

  llongs = test_db.get_A_time_span_seq_var();
  for (int i=0 ; i < llongs.size() ; i++)
    cout << "msecs(" << llongs[i] << ") ";
  cout << endl;

  val = test_db.get_An_any_point_var();
  cout << val->printed() << endl;

  val = test_db.get_A_rect_var();
  double width = val->lookup("width")->as_float();
  double height = val->lookup("height")->as_float();
  const char *color = val->lookup("color")->as_symb();
  x = val->lookup("bottom_left")->lookup("x")->as_int();
  y = val->lookup("bottom_left")->lookup("y")->as_int();
  printf("(bottom_left: %s, x: %d, y: %d, width: %f, height: %f, color: %s)\n\n",
    val->lookup("bottom_left")->printed().c_str(), x, y, width, height, color);

  static const int elems[10] = {0, 1, -1, 100, -1000, 2, -2, 10, -100, 1000};
  for (int i=0 ; i < 10 ; i++)
    printf("%d ", (int) test_db.in_An_int_unary_rel(elems[i]));
  putchar('\n');

  printf("[");
  vector<bool> boolv = test_db.get_A_bool_unary_rel();
  for (int i=0 ; i < boolv.size() ; i++)
    printf("%s%s", i == 0 ? "" : ", ", boolv[i] ? "true" : "false");
  puts("]\n");

  printf("[");
  vector<long long> intv = test_db.get_An_int_unary_rel();
  for (int i=0 ; i < intv.size() ; i++)
    printf("%s%lld", i == 0 ? "" : ", ", intv[i]);
  puts("]\n");

  printf("[");
  vector<double> floatv = test_db.get_A_float_unary_rel();
  for (int i=0 ; i < floatv.size() ; i++)
    printf("%s%f", i == 0 ? "" : ", ", floatv[i]);
  puts("]\n");

  printf("[");
  vector<const char *> symbv = test_db.get_A_symb_unary_rel();
  for (int i=0 ; i < symbv.size() ; i++)
    printf("%s%s", i == 0 ? "" : ", ", symbv[i]);
  puts("]\n");

  printf("[");
  vector<string> strv = test_db.get_A_string_unary_rel();
  for (int i=0 ; i < strv.size() ; i++)
    printf("%s\"%s\"", i == 0 ? "" : ", ", strv[i].c_str());
  puts("]\n");

  printf("[");
  vals = test_db.get_An_any_point_unary_rel();
  for (int i=0 ; i < vals.size() ; i++)
    printf("%s%s", i == 0 ? "" : ", ", vals[i]->printed().c_str());
  puts("]\n");

  //////////////////////////////////////////////////////////////////////////////

  vector<vector<bool> > boolvv = test_db.get_A_bool_seq_unary_rel();
  for (int i=0 ; i < boolvv.size() ; i++) {
    boolv = boolvv[i];
    for (int j=0 ; j < boolv.size() ; j++)
      printf("%s%s", j == 0 ? "" : " ", boolv[j] ? "true" : "false");
    putchar('\n');
  }
  putchar('\n');

  vector<vector<long long> > intvv = test_db.get_An_int_seq_unary_rel();
  for (int i=0 ; i < intvv.size() ; i++) {
    intv = intvv[i];
    for (int j=0 ; j < intv.size() ; j++)
      printf("%s%d", j == 0 ? "" : " ", (int) intv[j]);
    putchar('\n');
  }
  putchar('\n');

  vector<vector<double> > floatvv = test_db.get_A_float_seq_unary_rel();
  for (int i=0 ; i < floatvv.size() ; i++) {
    floatv = floatvv[i];
    for (int j=0 ; j < floatv.size() ; j++)
      printf("%s%f", j == 0 ? "" : " ", floatv[j]);
    putchar('\n');
  }
  putchar('\n');

  printf("[");
  vector<vector<const char *> > symbvv = test_db.get_A_symb_seq_unary_rel();
  for (int i=0 ; i < symbvv.size() ; i++) {
    symbv = symbvv[i];
    for (int j=0 ; j < symbv.size() ; j++)
      printf("%s%s", j == 0 ? "" : ", ", symbv[j]);
    printf("; ");
  }
  puts("]\n");

  printf("[");
  vector<vector<string> > strvv = test_db.get_A_string_seq_unary_rel();
  for (int i=0 ; i < strvv.size() ; i++) {
    strv = strvv[i];
    for (int j=0 ; j < strv.size() ; j++)
      printf("%s%s", i == 0 ? "" : ", ", strv[j].c_str());
    printf("; ");
  }
  puts("]\n");


  int memb_tests[8];

  memb_tests[0] = test_db.in_A_symb_float_binary_rel("pi", 314159e-5);
  memb_tests[1] = test_db.in_A_symb_float_binary_rel("e", 271828e-5);
  memb_tests[2] = test_db.in_A_symb_float_binary_rel("sqrt2", 141421e-5);
  memb_tests[3] = test_db.in_A_symb_float_binary_rel("sqrt3", 173205e-5);

  memb_tests[4] = test_db.in_A_symb_float_binary_rel("pi", 271828e-5);
  memb_tests[5] = test_db.in_A_symb_float_binary_rel("e", 314159e-5);
  memb_tests[6] = test_db.in_A_symb_float_binary_rel("sqrt2", 173205e-5);
  memb_tests[7] = test_db.in_A_symb_float_binary_rel("sqrt3", 141421e-5);

  for (int i=0 ; i < 8 ; i++)
    printf("%d ", memb_tests[i]);
  putchar('\n');


  printf("[");
  vector<tuple<const char *, double> > pairs_SF = test_db.get_A_symb_float_binary_rel();
  for (int i=0 ; i < pairs_SF.size() ; i++)
    printf("%s(%s, %f)", i == 0 ? "" : ", ", get<0>(pairs_SF[i]), get<1>(pairs_SF[i]));
  puts("]\n\n");

  const char *symbs_A[6] = {"pi", "e", "sqrt2", "sqrt3", "sqrt5", "non-key"};
  double doubles_A[5] = {271828e-5, 314159e-5, 173205e-5, 141421e-5, 223607e-5};
  for (int i=0 ; i < 6 ; i++) {
    const char *symb = symbs_A[i];
    printf("%s: ", symb);
    double d = 0;
    if (test_db.lookup_A_symb_float_binary_rel(symb, d))
      printf("%f\n", d);
    else
      printf("--\n");
  }
  putchar('\n');
  // for (int i=0 ; i < 5 ; i++) {
  //   printf("%f: ", doubles_A[i]);
  //   vector<const char *> results = test_db.bycol1_A_symb_float_binary_rel(doubles_A[i]);
  //   for (int j=0 ; j < results.size() ; j++)
  //     printf(" %s", results[j]);
  //   putchar('\n');
  // }
  // puts("\n");




  vector<tuple<bool, long long> > pairs_BI = test_db.get_A_bool_int_binary_rel();
  for (int i=0 ; i < pairs_BI.size() ; i++)
    printf("(%d, %lld) ", (int) get<0>(pairs_BI[i]), get<1>(pairs_BI[i]));
  putchar('\n');

  vector<tuple<string, vector<bool> > > pairs_SBS = test_db.get_A_string_bool_seq_binary_rel();
  for (int i=0 ; i < pairs_SBS.size() ; i++) {
    printf("(\"%s\", (", get<0>(pairs_SBS[i]).c_str());
    boolv = get<1>(pairs_SBS[i]);
    for (int j=0 ; j < boolv.size() ; j++)
      printf("%s%d", j > 0 ? ", " : "", (int) boolv[j]);
    printf(")) ");
  }
  putchar('\n');

  vector<tuple<vector<long long>, long long> > pairs_ISTS = test_db.get_An_int_seq_time_span_binary_rel();
  for (int i=0 ; i < pairs_ISTS.size() ; i++) {
    printf("((");
    vector<long long> llongv = get<0>(pairs_ISTS[i]);
    for (int j=0 ; j < llongv.size() ; j++)
      printf("%s%lld", j > 0 ? ", " : "", llongv[j]);
    printf("), %lld) ", get<1>(pairs_ISTS[i]));
  }
  puts("\n\n");

  printf("pi      = %8s %f\n", test_db.call_Lookup_by_float(314159e-5), test_db.call_Lookup_by_symb("pi"));
  printf("e       = %8s %f\n", test_db.call_Lookup_by_float(271828e-5), test_db.call_Lookup_by_symb("e"));
  printf("sqrt(2) = %8s %f\n", test_db.call_Lookup_by_float(141421e-5), test_db.call_Lookup_by_symb("sqrt2"));
  printf("sqrt(3) = %8s %f\n", test_db.call_Lookup_by_float(173205e-5), test_db.call_Lookup_by_symb("sqrt3"));

  // printf("pi      = %8s %s\n", test_db.call_Lookup("314159e-5").c_str(), test_db.call_Lookup("pi").c_str());
  // printf("e       = %8s %s\n", test_db.call_Lookup("271828e-5").c_str(), test_db.call_Lookup("e").c_str());
  // printf("sqrt(2) = %8s %s\n", test_db.call_Lookup("141421e-5").c_str(), test_db.call_Lookup("sqrt2").c_str());
  // printf("sqrt(3) = %8s %s\n", test_db.call_Lookup("173205e-5").c_str(), test_db.call_Lookup("sqrt3").c_str());

  printf("pi      = %8s %s\n", test_db.call_Lookup("3.14159")->printed().c_str(), test_db.call_Lookup("pi")->printed().c_str());
  printf("e       = %8s %s\n", test_db.call_Lookup("2.71828")->printed().c_str(), test_db.call_Lookup("e")->printed().c_str());
  printf("sqrt(2) = %8s %s\n", test_db.call_Lookup("1.41421")->printed().c_str(), test_db.call_Lookup("sqrt2")->printed().c_str());
  printf("sqrt(3) = %8s %s\n", test_db.call_Lookup("1.73205")->printed().c_str(), test_db.call_Lookup("sqrt3")->printed().c_str());

  // test_db.call_Lookup("314159e-5");

  // std::string call_Lookup(const char *);
  // std::string call_Alt_lookup(const char *);

  // double call_Lookup_by_symb(const char *);
  // const char *call_Lookup_by_float(double );

  // for b, i <- ((true, 0), (true, 1), (false, _neg_(1)), (false, 2), (true, _neg_(72305))):
  //   insert a_bool_int_binary_rel(b, i);
  // ;

  puts("");

  printf("%d -> %s\n",      0, test_db.call_Lookup_by_int(0) ? "true" : "false");
  printf("%d -> %s\n",      1, test_db.call_Lookup_by_int(1) ? "true" : "false");
  printf("%d -> %s\n",     -1, test_db.call_Lookup_by_int(-1) ? "true" : "false");
  printf("%d -> %s\n",      2, test_db.call_Lookup_by_int(2) ? "true" : "false");
  printf("%d -> %s\n", -72305, test_db.call_Lookup_by_int(-72305) ? "true" : "false");

  printf("%d -> %s\n",      0, test_db.call_Lookup("0")->printed().c_str());
  printf("%d -> %s\n",      1, test_db.call_Lookup("1")->printed().c_str());
  printf("%d -> %s\n",     -1, test_db.call_Lookup("-1")->printed().c_str());
  printf("%d -> %s\n",      2, test_db.call_Lookup("2")->printed().c_str());
  printf("%d -> %s\n", -72305, test_db.call_Lookup("-72305")->printed().c_str());

  puts("");
  fflush(stdout);

  cout << "\"010\"    -> " << test_db.call_Lookup_by_string("010")    << endl;
  cout << "\"100110\" -> " << test_db.call_Lookup_by_string("100110") << endl;
  cout << "\"\"       -> " << test_db.call_Lookup_by_string("")       << endl;

  // // cout << '"' << test_db.call_Alt_lookup("(false, true, false)") << '"' << endl;
  // // cout << '"' << test_db.call_Alt_lookup("(true, false, false, true, true, false)") << '"' << endl;
  // // cout << '"' << test_db.call_Alt_lookup("()") << '"' << endl << endl;

  cout << test_db.call_Alt_lookup("msecs(123)")->printed()      << " : ";
  cout << test_db.call_Alt_lookup("(0, 1, 2, 3)")->printed()    << endl;
  cout << test_db.call_Alt_lookup("msecs(98765)")->printed()    << " : ";
  cout << test_db.call_Alt_lookup("(9, 8, 7, 6, 5)")->printed() << endl;

  cout << endl;

  vector<tuple<const char *, double> > symb_float_pairs = test_db.call_Symbs_and_floats();
  for (int i=0 ; i < symb_float_pairs.size() ; i++)
    cout << "(" << get<0>(symb_float_pairs[i]) << ", " << get<1>(symb_float_pairs[i]) << ") ";
  cout << endl << endl;

  cout << test_db.call_Has_string_bool_seq_pair("010", "(false, true, false)") << endl;
  cout << test_db.call_Has_string_bool_seq_pair("100110", "(true, false, false, true, true, false)") << endl;
  cout << test_db.call_Has_string_bool_seq_pair("", "()") << endl;

  cout << test_db.call_Has_string_bool_seq_pair("010", "(false, true)") << endl;
  cout << test_db.call_Has_string_bool_seq_pair("100110", "(true, false, false)") << endl;
  cout << test_db.call_Has_string_bool_seq_pair("010", "(true, false, false, true, true, false)") << endl;
  cout << test_db.call_Has_string_bool_seq_pair("100110", "(false, true, false)") << endl;

  val = test_db.get_An_int_to_symb_map_var();
  cout << endl << val->printed() << endl << endl;

  cout << "msecs(123) -> ";
  if (test_db.lookup_An_int_seq_time_span_binary_rel("msecs(123)", llongs))
    cout << llongs;
  else
    cout << "--";
  cout << endl << endl;

  vector<tuple<long long, string, vector<double> > > triplev_I_S_FS = test_db.get_An_int_string_float_seq_ternary_rel();
  for (int i=0 ; i < triplev_I_S_FS.size() ; i++) {
    tuple<long long, string, vector<double> > &triple = triplev_I_S_FS[i];
    cout << get<0>(triple) << ", " << get<1>(triple) << ", " << get<2>(triple) << endl;
  }
  cout << endl;

  cout << test_db.in_An_int_string_float_seq_ternary_rel(0, "pi - e", "(3.14159, 2.71828)") << " ";
  cout << test_db.in_An_int_string_float_seq_ternary_rel(0, "sqrt(2) - sqrt(3)", "(1.41421, 1.73205)") << " ";
  cout << test_db.in_An_int_string_float_seq_ternary_rel(0, "sqrt(2) - sqrt(3)", "(141421e-5, 173205e-5)") << endl;
  cout << endl;

  vector<tuple<const char *, long long, vector<bool> > > triplev_S_I_BS = test_db.get_A_symb_int_bool_seq_ternary_rel();
  for (int i=0 ; i < triplev_S_I_BS.size() ; i++) {
    tuple<const char *, long long, vector<bool> > triple = triplev_S_I_BS[i];
    cout << get<0>(triple) << ", " << get<1>(triple) << ", " << get<2>(triple) << endl;
  }
  cout << endl;

  cout << test_db.in_A_symb_int_bool_seq_ternary_rel("one",   1, "(true)")                << " ";
  cout << test_db.in_A_symb_int_bool_seq_ternary_rel("two",   2, "(true, false)")         << " ";
  cout << test_db.in_A_symb_int_bool_seq_ternary_rel("three", 3, "(true, true)")          << " ";
  cout << test_db.in_A_symb_int_bool_seq_ternary_rel("four",  4, "(true, false, false)")  << " ";
  cout << endl;

  cout << test_db.in_A_symb_int_bool_seq_ternary_rel("(true)", 1, "one") << " ";
  cout << test_db.in_A_symb_int_bool_seq_ternary_rel("two",    2, "(false, false)") << " ";
  cout << test_db.in_A_symb_int_bool_seq_ternary_rel("three",  3, "(true)") << " ";
  cout << test_db.in_A_symb_int_bool_seq_ternary_rel("four",   5, "(true, false, false)") << " ";

  cout << endl << endl;

  unique_ptr<Value> state = test_db.read_state();
  state->print(cout);
  cout << endl << endl;
}

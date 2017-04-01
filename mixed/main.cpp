#include "common.h"


void release_all_cached_objs();
uint32 get_live_objs_count();
uint32 get_max_live_objs_count();
uint32 get_total_objs_count();


void run_TrAutoA_tests(const char *file, bool set_state);


int main(int argc, char **argv) {
  char filename[1024];

  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <directory>" << endl;
    return -1;
  }

  sprintf(filename, "%s/state-A0.txt", argv[1]);
  run_TrAutoA_tests(filename, true);

  cout << "\n\n" << string(80, '#') << "\n\n" << endl;

  sprintf(filename, "%s/msg-A0.txt", argv[1]);
  run_TrAutoA_tests(filename, false);

  cout << "\n\n" << endl;

  release_all_cached_objs();
  fprintf(stderr, "\nNumber of live objects: %d\n", get_live_objs_count());
  fprintf(stderr, "Max number of live objects: %d\n", get_max_live_objs_count());
  fprintf(stderr, "Total number of allocated objects: %d\n", get_total_objs_count());
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// vector<long long> as_long_long_vector(Value *value) {
//   unsigned int len = value->size();
//   vector<long long> result(len);
//   for (unsigned int i=0 ; i < len ; i++)
//     result[i] = value->item(i)->as_int();
//   return result;
// }

////////////////////////////////////////////////////////////////////////////////

// void run_MyTrAuto_tests(char *file) {
//   MyMinTrAuto test_db;

//   // if (file != NULL) {
//   //   char buffer[65536];
//   //   FILE *fp = fopen(file, "r");
//   //   if (fp == NULL) {
//   //     printf("Cannot open file %s\n", file);
//   //     return;
//   //   }
//   //   int count = fread(buffer, 1, 32768, fp);
//   //   buffer[count] = '\0';
//   //   fclose(fp);
//   //   // test_db.set_state(buffer);
//   //   test_db.execute(buffer);
//   //
//   // }
//   // else {
//   //   test_db.execute("my_msg");
//   // }

//   vector<unique_ptr<Value> > ps = test_db.get_An_any_point_set_var();
//   for (int i=0 ; i < ps.size() ; i++)
//     cout << ps[i]->printed() << " ";
//   cout << endl << endl << endl;

//   unique_ptr<Value> state = test_db.read_state();
//   state->print(cout);
//   cout << endl << endl;
// }

////////////////////////////////////////////////////////////////////////////////

#ifndef SIMPLIFICATION_H_
#define SIMPLIFICATION_H_
class mani_string
{
   private:
      bool next_simp;
      int intdata[1000];
      bool invert_sign;
      float floatdata[1000];
      char argu_ment[500]; 
      char input[1000],operate[1000];
   public:
      class error1 {};
      class error2 {};
      int remove_outermost_brace(char ch[]);
      void insert(char [],int ,int );
      void calc_pow();
      void mult_signs();
      int pos_pre_float(int c_pos);
      int pos_post_char(int c_pos);
      void num_to_char(char [],int ,int &);
      void make_string();
      void separate_int_char();
      void separate_float_char();
      void div_mult();
      void simplify_floats();
      void simplifying(char []);
      void simplification(char []);
      int term_in_braces(char [],char [],int &, int &);
      bool remove_braces();
      int read_expression();
      void simplify();
      void show_result();
      void rep_x(char [], float);
};
#endif

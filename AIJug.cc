#include "Player.hh"
#include <set>

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Jug


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */

    //REMINDER: i = fila, j = columna.

    void zombie_mata(Pos ini, Dir &d) {
      vector<vector<bool>> vist(60, vector <bool> (60, false));
      vector< vector <Pos>> pare(60, vector <Pos>(60));
      vector<vector<int> > dist(60, vector<int>(60));
      queue<Pos> cua;
      cua.push(ini);
      dist[ini.i][ini.j] = 0;
      bool acaba = false;
      while(!acaba) {
        Pos p = cua.front();
        int x = p.i;
        int y = p.j;
        cua.pop();
        if(dist[x][y] > 5) acaba = true;
        if(((cell(p).owner != -1) and (cell(p).owner != me()) and (cell(p).id != -1) and (unit(cell(p).id).type == Alive)) or ((cell(p).owner == -1) and (cell(p).id != -1))) {  //mata
          vector <Pos> vec;
          int x2;
          int y2;
          int dista = dist[x][y];
          while(dista > 0) {
            vec.push_back(p);
            x2 = pare[x][y].i;
            y2 = pare[x][y].j;
            x = x2;
            y = y2;
            p.i = x;
            p.j = y;
            --dista;
          }
          int new_x = vec[vec.size()-1].i;
          int new_y = vec[vec.size()-1].j;
          if (ini.j > new_y) d = Left;
          else if (ini.j < new_y) d = Right;
          else if (ini.i > new_x) d = Up;
          else if (ini.i < new_x) d = Down;
          return;
          }
        vist[x][y] = true;
        Pos p2 = p+Down;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
        p2 = p+Up;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
        p2 = p+Left;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
        p2 = p+Right;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
      }
      bool nofares = false;
      mou_random(ini, nofares, d);
    }

    void safe_zone(Pos ini, bool &danger, Dir &d, bool &stop) {
      vector<vector<bool>> vist(60, vector <bool> (60, false));
      vector< vector <Pos>> pare(60, vector <Pos>(60));
      vector<vector<int> > dist(60, vector<int>(60));
      queue<Pos> cua;
      cua.push(ini);
      dist[ini.i][ini.j] = 0;
      bool acaba = false;
      while(!acaba) {
        Pos p = cua.front();
        int x = p.i;
        int y = p.j;
        cua.pop();
        if(dist[x][y] > 10) acaba = true;
        if((cell(p).owner != -1) and (cell(p).owner != me()) and (cell(p).id != -1) and (unit(cell(p).id).type == Alive)) {  //enemigos
          danger = true;
          int enemic = cell(p).owner;
          int dista = dist[x][y];
          vector <Pos> vec;
          int x2;
          int y2;
          while(dista > 0) {
            vec.push_back(p);
            x2 = pare[x][y].i;
            y2 = pare[x][y].j;
            x = x2;
            y = y2;
            p.i = x;
            p.j = y;
            --dista;
          }
          int new_x = vec[vec.size()-1].i;
          int new_y = vec[vec.size()-1].j;
          if (ini.j > new_y) d = Left;
          else if (ini.j < new_y) d = Right;
          else if (ini.i > new_x) d = Up;
          else if (ini.i < new_x) d = Down;
          return;
        }
        if((cell(p).owner == -1) and (cell(p).id != -1)) {  //zombies (EDIT) TIENE Q SER 5, HACER DE NUVEOOOOOO
          danger = true;
          int dista = dist[x][y];
          vector <Pos> vec;
          int x2;
          int y2;
          while(dista > 0) {
            vec.push_back(p);
            x2 = pare[x][y].i;
            y2 = pare[x][y].j;
            x = x2;
            y = y2;
            p.i = x;
            p.j = y;
            --dista;
          }
          int new_x = vec[vec.size()-1].i;
          int new_y = vec[vec.size()-1].j;
          if (ini.j > new_y) d = Left;
          else if (ini.j < new_y) d = Right;
          else if (ini.i > new_x) d = Up;
          else if (ini.i < new_x) d = Down;
          return;
        }
        vist[x][y] = true;
        Pos p2 = p+Down;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
        p2 = p+Up;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
        p2 = p+Left;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
        p2 = p+Right;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
      }
      danger = false;
    }

    void busca_menjar(Pos ini, bool &soc_primer, Dir &d) {
      vector<vector<bool>> vist(60, vector <bool> (60, false));
      vector< vector <Pos>> pare(60, vector <Pos>(60));
      vector<vector<int> > dist(60, vector<int>(60));
      queue<Pos> cua;
      cua.push(ini);
      dist[ini.i][ini.j] = 0;
      bool acaba = false;
      while(!acaba) {
        Pos p = cua.front();
        int x = p.i;
        int y = p.j;
        cua.pop();
        if(dist[x][y] > 12) acaba = true;
        if(cell(p).food == true) {
          soc_primer = bfs_menjar(p);
          if(soc_primer) {
              int dista = dist[x][y];
              vector <Pos> vec;
              int x2;
              int y2;
              while(dista > 0) {
                  vec.push_back(p);
                  x2 = pare[x][y].i;
                  y2 = pare[x][y].j;
                  x = x2;
                  y = y2;
                  p.i = x;
                  p.j = y;
                  --dista;
              }
              int new_x = vec[vec.size()-1].i;
              int new_y = vec[vec.size()-1].j;
              if (ini.j > new_y) d = Left;
              else if (ini.j < new_y) d = Right;
              else if (ini.i > new_x) d = Up;
              else if (ini.i < new_x) d = Down;
              return;
          }
          else {
            return;
          }
        }
        vist[x][y] = true;
        Pos p2 = p+Down;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
        p2 = p+Up;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
        p2 = p+Left;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
        p2 = p+Right;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
      }
    }

    bool bfs_menjar(Pos ini) {
      vector<vector<bool>> vist(60, vector <bool> (60, false));
      vector< vector <Pos>> pare(60, vector <Pos>(60));
      vector<vector<int> > dist(60, vector<int>(60));
      queue<Pos> cua;
      cua.push(ini);
      dist[ini.i][ini.j] = 0;
      bool acaba = false;
      while(!acaba) {
        Pos p = cua.front();
        int x = p.i;
        int y = p.j;
        cua.pop();
        if(dist[x][y] > 12) acaba = true;
        if((cell(p).owner != -1) and (cell(p).id != -1)) {
            if(cell(p).owner == me()) return true;
            else return false;
        }
        vist[x][y] = true;
        Pos p2 = p+Down;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
        p2 = p+Up;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
        p2 = p+Left;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
        p2 = p+Right;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
      }
      return false;
    }
    
    void mou_random(Pos ini, bool &fallo, Dir &d) {
      vector<Dir> dirs;
      Pos p2 = ini+Down;
      if (pos_ok(p2) and cell(p2).type != Waste and cell(p2).owner != me()) dirs.push_back(Down);
      p2 = ini+Up;
      if (pos_ok(p2) and cell(p2).type != Waste and cell(p2).owner != me()) dirs.push_back(Up);
      p2 = ini+Left;
      if (pos_ok(p2) and cell(p2).type != Waste and cell(p2).owner != me()) dirs.push_back(Left);
      p2 = ini+Right;
      if (pos_ok(p2) and cell(p2).type != Waste and cell(p2).owner != me()) dirs.push_back(Right);

      if(dirs.size() > 0) {
        d = dirs[random(0,dirs.size()-1)];
        return;
      }
      else {
        fallo = true;
        return;
      }
    }

    void mou_inteligent(Pos ini, Dir &d) {
      vector<vector<bool>> vist(60, vector <bool> (60, false));
      vector< vector <Pos>> pare(60, vector <Pos>(60));
      vector<vector<int> > dist(60, vector<int>(60));
      queue<Pos> cua;
      cua.push(ini);
      dist[ini.i][ini.j] = 0;
      bool acaba = false;
      while(!acaba) {
        Pos p = cua.front();
        int x = p.i;
        int y = p.j;
        cua.pop();
        if(dist[x][y] > 40) acaba = true;
        if(cell(p).owner != me()) {
          int dista = dist[x][y];
          vector <Pos> vec;
          int x2;
          int y2;
          while(dista > 0) {
              vec.push_back(p);
              x2 = pare[x][y].i;
              y2 = pare[x][y].j;
              x = x2;
              y = y2;
              p.i = x;
              p.j = y;
              --dista;
          }
          int new_x = vec[vec.size()-1].i;
          int new_y = vec[vec.size()-1].j;
          if (ini.j > new_y) d = Left;
          else if (ini.j < new_y) d = Right;
          else if (ini.i > new_x) d = Up;
          else if (ini.i < new_x) d = Down;
          return;
        }
        vist[x][y] = true;
        Pos p2 = p+Down;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
        p2 = p+Up;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
        p2 = p+Left;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
        p2 = p+Right;
        if (pos_ok(p2) and cell(p2).type != Waste and !vist[p2.i][p2.j]) {
          pare[p2.i][p2.j] = p;
          cua.push(p2);
          dist[p2.i][p2.j] = dist[x][y] + 1;
        }
      }
      //else mou random
      vector<Dir> dirs;
      Pos p2 = ini+Down;
      if (pos_ok(p2) and cell(p2).type != Waste) dirs.push_back(Down);
      p2 = ini+Up;
      if (pos_ok(p2) and cell(p2).type != Waste) dirs.push_back(Up);
      p2 = ini+Left;
      if (pos_ok(p2) and cell(p2).type != Waste) dirs.push_back(Left);
      p2 = ini+Right;
      if (pos_ok(p2) and cell(p2).type != Waste) dirs.push_back(Right);

      d = dirs[random(0,dirs.size()-1)];
    }


  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {

      vector<int> alive = alive_units(me());

      for (int id : alive) {
        if(unit(id).rounds_for_zombie != -1) {
          Dir d;
          zombie_mata(unit(id).pos, d);
          move(id, d);
        }
        else {
          Dir d_menjar;
          bool soc_primer = false;
          busca_menjar(unit(id).pos, soc_primer, d_menjar);
          if(soc_primer) move(id, d_menjar);
          else {
            Dir d_safe;
            bool danger = false;
            bool stop = false;
            safe_zone(unit(id).pos, danger, d_safe, stop); //HACER SAFE ZONE SEPARADOS PARA ZOMBIES Y ENEMIGOS, (FALTA ZOMBIE)
            if(danger) {
              if(!stop) move(id, d_safe);
            }
            else {
              bool fallo = false;
              Dir d_mou;
              mou_random(unit(id).pos, fallo, d_mou);
              if(!fallo) move(id, d_mou);
              else {
                Dir d_mou_iq;
                mou_inteligent(unit(id).pos, d_mou_iq);
                move(id, d_mou_iq);
              }
            }
          }
        }
      }

  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);

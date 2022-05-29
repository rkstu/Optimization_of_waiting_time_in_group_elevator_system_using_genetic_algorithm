#include <bits/stdc++.h>
using namespace std;

#define TF 2
#define PT 7
// #define

int totalFloors(vector<int> floors);

// Lift class for lift
class Lift
{
public:
  bool dir;
  int curr_f;
  vector<int> des;
  vector<string> assing;
  int hc_df_up_max = INT_MIN, hc_up_min = INT_MAX;
  int hc_down_max = INT_MIN, hc_df_down_min = INT_MAX;
  int duration = 0;

  Lift() {}
  void set(bool dir, int curr_f, vector<int> des)
  {
    this->dir = dir;
    this->curr_f = curr_f;
    if (dir)
    {
      sort(des.begin(), des.end());
    }
    else
    {
      sort(des.begin(), des.end(), greater<int>());
    }
    des.insert(des.begin(), curr_f);
    this->des = des;
  }
  int finalDes() { return des[des.size() - 1]; }
  void calulateDuration(int hc, int hcd)
  {
    vector<int> temp_des{des.begin() + 1, des.end()};
    temp_des.push_back(hc);
    sort(temp_des.begin(), temp_des.end());
    temp_des.push_back(hcd);
    temp_des.insert(temp_des.begin(), curr_f);
    int nFloors = totalFloors(temp_des);
    duration = nFloors * TF + (des.size() - 1) * PT;
  }
};

// Hall calls class
class Request
{
public:
  int hc, hcd;
  bool dir;
  void set(bool dir, int hc, int hcd)
  {
    this->dir = dir;
    this->hc = hc;
    this->hcd = hcd;
  }
};

int totalFloors(vector<int> floors)
{
  int sum = 0;
  for (int i = 0; i < floors.size() - 1; i++)
  {
    sum += abs(floors[i + 1] - floors[i]);
  }
  return abs(sum);
}

int MAX(Request req, int car_df, Lift car)
{
  int hcDesUpMax = 0, hcDownMax = 0;
  if (req.dir == 1)
  {
    hcDesUpMax = req.hcd;
  }
  hcDesUpMax = max(hcDesUpMax, car.hc_df_up_max);
  if (req.dir == 0)
  {
    hcDownMax = req.hc;
  }
  hcDownMax = max(hcDownMax, car.hc_down_max);
  return max(hcDesUpMax, max(car_df, hcDownMax));
}
int MIN(Request req, Lift car)
{
  int hcDesDownMin = 0, hcUpMin = 0;
  if (req.dir == 0)
  {
    hcDesDownMin = req.hcd;
  }
  hcDesDownMin = min(hcDesDownMin, car.hc_df_down_min);
  if (req.dir == 1)
  {
    hcUpMin = req.hc;
  }
  hcUpMin = min(hcUpMin, car.hc_up_min);
  return min(hcDesDownMin, hcUpMin);
}

int main()
{

  // Test data
  Lift car[4];
  car[0].set(1, 5, vector<int>{7});

  car[1].set(0, 17, vector<int>{8});
  car[2].set(1, 3, vector<int>{18, 20});
  car[3].set(0, 19, vector<int>{1, 6});

  Request req[6];
  req[0].set(0, 7, 1);
  req[1].set(1, 9, 16);
  req[2].set(0, 11, 2);
  req[3].set(1, 12, 20);
  req[4].set(0, 13, 6);
  req[5].set(0, 15, 9);

  // Applying Algorithem
  for (int i = 0; i < 6; i++)
  {
    pair<int, int> timmer;
    timmer = {INT_MAX, 0};
    for (int j = 0; j < 4; j++)
    {
      set<int> st;
      st.insert(car[j].curr_f);
      // if (car[j].finalDes() < req[i].hcd)
      // {
      st.insert(car[j].finalDes());
      // }
      st.insert(req[i].hc);
      st.insert(req[i].hcd);
      int ns = st.size() - 2;
      int interval = 0;
      int mn = MIN(req[i], car[j]), mx = MAX(req[i], car[j].finalDes(), car[j]);

      if (car[j].dir == 1)
      {
        if (req[i].hc >= car[j].curr_f && req[i].dir == 1)
        {
          interval = (req[i].hc - car[j].curr_f) * TF + ns * PT;
        }
        else if (req[i].dir == 0)
        {
          interval = (2 * mx - car[j].curr_f - req[i].hc) * TF + ns * PT;
        }
        else if (req[i].hc < car[j].curr_f && req[i].dir == 1)
        {
          interval = (2 * mx - car[j].curr_f + req[i].hc - 2 * mn) * TF + ns * PT;
        }
      }
      else
      {
        if (req[i].hc <= car[j].curr_f && req[i].dir == 0)
        {
          interval = (car[j].curr_f - req[i].hc) * TF + ns * PT;
        }
        else if (req[i].dir == 1)
        {
          interval = (car[j].curr_f + req[i].hc - 2 * mn) * TF + ns * PT;
        }
        else if (req[i].hc > car[j].curr_f)
        {
          interval = (2 * mx + car[j].curr_f - req[i].hc - 2 * mn) * TF + ns * PT;
        }
      }
      // Adding duration
      car[j].calulateDuration(req[i].hc, req[i].hcd);
      interval += car[j].duration;

      // comparing waiting time for each lift
      if (timmer.first > interval)
      {
        timmer.first = interval;
        timmer.second = j;
      }
    }
    // temp_car == index of the lift with minimum waiting time
    int temp_car = timmer.second;
    car[temp_car].assing.push_back("HC-" + to_string(req[i].hc));

    // pushing floors
    if (car[temp_car].finalDes() != req[i].hc)
    {
      car[temp_car].des.push_back(req[i].hc);
    }
    car[temp_car].des.push_back(req[i].hcd);
    car[temp_car].dir != car[temp_car].dir;

    // updating values
    if (req[i].dir == 1)
    {
      car[temp_car].hc_df_up_max = max(req[i].hcd, car[temp_car].hc_df_up_max);
      car[temp_car].hc_up_min = min(req[i].hc, car[temp_car].hc_up_min);
    }
    else
    {
      car[temp_car].hc_down_max = max(req[i].hc, car[temp_car].hc_down_max);
      car[temp_car].hc_df_down_min = max(req[i].hcd, car[temp_car].hc_df_down_min);
    }
    // updating destination vector
    set<int> st_temp;
    for (int z = 1; z < car[temp_car].des.size(); z++)
    {
      st_temp.insert(car[temp_car].des[z]);
    }
    int curr_f = car[temp_car].curr_f;
    car[temp_car].des.clear();
    car[temp_car].des.push_back(curr_f);
    for (auto it = st_temp.begin(); it != st_temp.end(); it++)
    {
      car[temp_car].des.push_back(*it);
    }

    // updating lift direction
    car[temp_car].dir = req[i].dir;
  }

  // Result according to the algorithem
  cout << "\n Floor wise stops \n";
  for (int i = 0; i < 4; i++)
  {
    vector<int> temp_des = car[i].des;
    cout << "For Car " << i + 1 << " : ";
    for (int j = 0; j < temp_des.size() - 1; j++)
    {
      cout << temp_des[j] << "-> ";
    }
    cout << temp_des[temp_des.size() - 1] << endl;
  }

  cout << "\n Assigned Hall calls  \n";
  for (int i = 0; i < 4; i++)
  {
    vector<string> temp_des = car[i].assing;
    cout << "For Car " << i + 1 << " : ";
    for (int j = 0; j < temp_des.size(); j++)
    {
      cout << temp_des[j] << " ";
    }
    cout << endl;
  }

  return 0;
}
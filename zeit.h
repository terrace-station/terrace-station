#ifndef ZEIT_HH // bedingtes Einbinden
#define ZEIT_HH

#include <sys/time.h>

// void zeit_aktualisieren(float& aktuelle_zeit_, timeval& aktuelle_zeit_referenz_)
// {
//   timeval zeit_;
//   gettimeofday(&zeit_, 0);
//   aktuelle_zeit_ += (0.000001*aktuelle_zeit_referenz_.tv_usec + float(aktuelle_zeit_referenz_.tv_sec%3600)) - (0.000001*zeit_.tv_usec + float(zeit_.tv_sec%3600));
//   aktuelle_zeit_referenz = zeit_;
// }

static float zeit_diff(timeval& zeit_alt)
{
    float zeit_diff_; 
    timeval zeit_;
    gettimeofday(&zeit_, 0);
    zeit_diff_ += (0.000001*zeit_.tv_usec + float(zeit_.tv_sec%3600)) - (0.000001*zeit_alt.tv_usec + float(zeit_alt.tv_sec%3600));
    zeit_alt = zeit_;
    return zeit_diff_;
}

static float zeit_aktuell()
{
   float zeit_aktuell_;
   timeval zeit_;
   gettimeofday(&zeit_, 0);
   zeit_aktuell_ = (0.000001*zeit_.tv_usec + float(zeit_.tv_sec%3600));
   return zeit_aktuell_;
}

static float dreieck(float t)
{
  t -= int(t);
  if (t < 0.25)
    return t;
  else if (t < 0.75)
    return 0.5-t;
  else
    return t-1.0;
}

#endif
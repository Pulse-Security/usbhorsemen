#include <Mouse.h>

bool led_state = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  for (uint8_t i = 0; i < 5; i++){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }

  randomSeed(analogRead(0));
  Mouse.begin();
}

// Bresenham line
void plot_line(int x0, int y0, int x1, int y1)
{
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy, e2;

  int px = 0;
  int py = 0;
  for (;;){
    Mouse.move(x0-px,y0-py,0);
    px = x0;
    py = y0;
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; }
    if (e2 <= dx) { err += dx; y0 += sy; }
  }
}

typedef struct {
  int8_t x;
  int8_t y;
} t_coord;

// points referenced from an x,y 0,0 origin
t_coord points[] = {
  {-42,-127},
  {-88,0},
  {18,-88},
  {-102,-88},
  {0,0},

  // artisinal, hand-placed, farm-to-table pixels
  {2,0},{1,0},{0,1},{-1,2},{-2,3},{-3,3},{-4,4},{-5,5},{-6,5},{-7,6},{-8,6},{-9,7},{-10,7},{-11,8},{-12,8},{-13,9},{-14,9},{-15,10},{-16,10},{-17,10},{-18,11},{-19,11},{-20,12},{-21,12},{-22,12},{-23,12},{-24,13},{-25,13},{-26,13},{-27,13},{-28,14},{-29,14},{-30,14},{-31,14},{-32,14},{-33,14},{-34,15},{-35,15},{-36,15},{-37,15},{-38,15},{-39,15},{-40,15},{-41,15},
  {-42,15},{-43,15},{-44,15},{-45,15},{-46,15},{-47,15},{-48,15},{-49,15},{-50,15},{-51,14},{-52,14},{-53,14},{-54,14},{-55,14},{-56,14},{-57,13},{-58,13},{-59,13},{-60,13},{-61,12},{-62,12},{-63,12},{-64,12},{-65,11},{-66,11},{-67,10},{-68,10},{-69,10},{-70,9},{-71,9},{-72,8},{-73,8},{-74,7},{-75,7},{-76,6},{-77,6},{-78,5},{-79,5},{-80,4},{-81,3},{-82,3},{-83,2},{-84,1},{-85,0},{-86,0},{-87,-1},{-88,-2},{-89,-3},{-90,-4},{-91,-5},{-92,-6},{-93,-7},{-94,-8},{-95,-9},{-96,-10},{-97,-11},{-98,-12},{-98,-13},{-99,-14},{-100,-15},{-101,-16},{-101,-17},{-102,-18},{-103,-19},{-103,-20},{-104,-21},{-104,-22},{-105,-23},{-105,-24},{-106,-25},{-106,-26},{-107,-27},{-107,-28},{-108,-29},{-108,-30},{-108,-31},{-109,-32},{-109,-33},{-110,-34},{-110,-35},{-110,-36},{-110,-37},{-111,-38},{-111,-39},{-111,-40},{-111,-41},{-112,-42},{-112,-43},{-112,-44},{-112,-45},{-112,-46},{-112,-47},{-113,-48},{-113,-49},{-113,-50},{-113,-51},{-113,-52},{-113,-53},{-113,-54},{-113,-55},
  {-113,-56},{-113,-57},{-113,-58},{-113,-59},{-113,-60},{-113,-61},{-113,-62},{-113,-63},{-113,-64},{-112,-65},{-112,-66},{-112,-67},{-112,-68},{-112,-69},{-112,-70},{-111,-71},{-111,-72},{-111,-73},{-111,-74},{-110,-75},{-110,-76},{-110,-77},{-110,-78},{-109,-79},{-109,-80},{-108,-81},{-108,-82},{-108,-83},{-107,-84},{-107,-85},{-106,-86},{-106,-87},{-105,-88},{-105,-89},{-104,-90},{-104,-91},{-103,-92},{-103,-93},{-102,-94},{-101,-95},{-101,-96},{-100,-97},{-99,-98},{-98,-99},{-98,-100},{-97,-101},{-96,-102},{-95,-103},{-94,-104},{-93,-105},{-92,-106},{-91,-107},{-90,-108},{-89,-109},{-88,-110},{-87,-111},{-86,-112},{-85,-112},{-84,-113},{-83,-114},{-82,-115},{-81,-115},{-80,-116},{-79,-117},{-78,-117},{-77,-118},{-76,-118},{-75,-119},{-74,-119},{-73,-120},{-72,-120},{-71,-121},{-70,-121},{-69,-122},{-68,-122},{-67,-122},{-66,-123},{-65,-123},{-64,-124},{-63,-124},{-62,-124},{-61,-124},{-60,-125},{-59,-125},{-58,-125},{-57,-125},{-56,-126},{-55,-126},{-54,-126},{-53,-126},{-52,-126},{-51,-126},{-50,-127},{-49,-127},{-48,-127},{-47,-127},{-46,-127},{-45,-127},{-44,-127},{-43,-127},
  {-42,-127},{-41,-127},{-40,-127},{-39,-127},{-38,-127},{-37,-127},{-36,-127},{-35,-127},{-34,-127},{-33,-126},{-32,-126},{-31,-126},{-30,-126},{-29,-126},{-28,-126},{-27,-125},{-26,-125},{-25,-125},{-24,-125},{-23,-124},{-22,-124},{-21,-124},{-20,-124},{-19,-123},{-18,-123},{-17,-122},{-16,-122},{-15,-122},{-14,-121},{-13,-121},{-12,-120},{-11,-120},{-10,-119},{-9,-119},{-8,-118},{-7,-118},{-6,-117},{-5,-117},{-4,-116},{-3,-115},{-2,-115},{-1,-114},{0,-113},{1,-112},{2,-112},{3,-111},{4,-110},{5,-109},{6,-108},{7,-107},{8,-106},{9,-105},{10,-104},{11,-103},{12,-102},{13,-101},{14,-100},{14,-99},{15,-98},{16,-97},{17,-96},{17,-95},{18,-94},{19,-93},{19,-92},{20,-91},{20,-90},{21,-89},{21,-88},{22,-87},{22,-86},{23,-85},{23,-84},{24,-83},{24,-82},{24,-81},{25,-80},{25,-79},{26,-78},{26,-77},{26,-76},{26,-75},{27,-74},{27,-73},{27,-72},{27,-71},{28,-70},{28,-69},{28,-68},{28,-67},{28,-66},{28,-65},{29,-64},{29,-63},{29,-62},{29,-61},{29,-60},{29,-59},{29,-58},{29,-57},
  {29,-56},{29,-55},{29,-54},{29,-53},{29,-52},{29,-51},{29,-50},{29,-49},{29,-48},{28,-47},{28,-46},{28,-45},{28,-44},{28,-43},{28,-42},{27,-41},{27,-40},{27,-39},{27,-38},{26,-37},{26,-36},{26,-35},{26,-34},{25,-33},{25,-32},{24,-31},{24,-30},{24,-29},{23,-28},{23,-27},{22,-26},{22,-25},{21,-24},{21,-23},{20,-22},{20,-21},{19,-20},{19,-19},{18,-18},{17,-17},{17,-16},{16,-15},{15,-14},{14,-13},{14,-12},{13,-11},{12,-10},{11,-9},{10,-8},{9,-7},{8,-6},{7,-5},{6,-4},{5,-3},{4,-2},{3,-1},
  {0,0},
};

void loop() {
  digitalWrite(LED_BUILTIN, led_state);
  led_state = !led_state;

  for(int i = 0; i < sizeof(points) / sizeof(t_coord); i++){
    int x = points[i].x;
    int y = points[i].y;
  
    if(i == 0){
      plot_line(0, 0, x, y);
    } else {
      plot_line(0, 0, x - points[i-1].x, y - points[i-1].y);
    }
    delay(10);
  }

  Mouse.move(random(-512, 512), random(-512, 512), 0);
}
// SDL_Test.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Project_SDL1.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <random>
#include <string>

void init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)
    throw std::runtime_error("init():" + std::string(SDL_GetError()));

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
    throw std::runtime_error("init(): SDL_image could not initialize! "
                             "SDL_image Error: " +
                             std::string(IMG_GetError()));
}

namespace {
// Defining a namespace without a name -> Anonymous workspace
// Its purpose is to indicate to the compiler that everything
// inside of it is UNIQUELY used within this source file.

SDL_Surface* load_surface_for(const std::string& path,
                              SDL_Surface* window_surface_ptr) {

  // Helper function to load a png for a specific surface
  // See SDL_ConvertSurface
}
} // namespace


//Animal
animal::animal(const std::string& file_path, SDL_Surface* window_surface_ptr)
      :

        window_surface_ptr_{window_surface_ptr},
        image_ptr_{IMG_Load(file_path.c_str())}, position_{0, 0, 100, 100} {};

  animal::~animal() {
    SDL_FreeSurface(image_ptr_);
    SDL_FreeSurface(window_surface_ptr_);
  }; 

  void animal::draw() {
    SDL_BlitScaled(image_ptr_, NULL, window_surface_ptr_, &position_);
  }; 

  void animal::move() {} // todo: Animals move around, but in a different
                           // fashion depending on which type of animal



//Sheep
sheep::sheep(SDL_Surface* window_surface_ptr)
      : 
      window_surface_ptr_{window_surface_ptr},
      image_ptr_{IMG_Load("Images/MOUTON.png")},
      animal{"Images/MOUTON.png",window_surface_ptr}
        {};

  sheep::~sheep() { 
    SDL_FreeSurface(window_surface_ptr_);
    SDL_FreeSurface(image_ptr_);

  }

  void sheep::move() 
  { 
    SDL_BlitScaled(image_ptr_, NULL, window_surface_ptr_, &position_);
    position_.x += 2;
    position_.y += 2;
    
  }
  void sheep::draw() { animal::draw(); }



//Ground  
ground::ground(SDL_Surface* window_surface_ptr)
        : window_surface_ptr_{window_surface_ptr} {}; 

ground::~ground() {
    SDL_FreeSurface(window_surface_ptr_);
}; 

void ground::add_animal(animal* animal) {
    animals.push_back(animal);
}; 

void ground::update() {
    for (int i = 0; i < animals.size(); i++) {
    animals.at(i)->move();
    animals.at(i)->draw();
    }
}; 
 

application::application(unsigned n_sheep, unsigned n_wolf)
          : window_ptr_{SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED,
                                         SDL_WINDOWPOS_UNDEFINED, frame_width,
                                         frame_height, SDL_WINDOW_OPENGL)},
            window_surface_ptr_{SDL_GetWindowSurface(window_ptr_)},
            window_event_{}, ground_app_{ground(window_surface_ptr_)}
            //,
            // n_sheep_{n_sheep}
            {}; // Ctor

application::~application() {
        SDL_DestroyWindow(window_ptr_);
        SDL_FreeSurface(window_surface_ptr_);
     }; // dtor

int application::loop(unsigned period) {
SDL_FillRect(window_surface_ptr_, NULL, 888);

// for (int i = 0; i < n_sheep_; i++) {
sheep Sheep1 = sheep(window_surface_ptr_);
ground_app_.add_animal(&Sheep1);
//}

int current_time = SDL_GetTicks();
int last_time;
while (current_time < period) {
    last_time = SDL_GetTicks();
    std::cout << "last_time: " << last_time << std::endl;

    SDL_FillRect(window_surface_ptr_, NULL, 888);
    ground_app_.update();
    current_time = SDL_GetTicks();
    int sleep = 50 - (current_time - last_time);
    SDL_Delay(sleep);
    SDL_UpdateWindowSurface(window_ptr_);
}

SDL_DestroyWindow(window_ptr_);
SDL_Quit();
return 0;
};
   
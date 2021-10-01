// SDL_Test.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <vector>

// Defintions
constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1. / frame_rate;
constexpr unsigned frame_width = 1400; // Width of window in pixel
constexpr unsigned frame_height = 900; // Height of window in pixel
// Minimal distance of animals to the border
// of the screen
constexpr unsigned frame_boundary = 100;

// Helper function to initialize SDL
void init();

class animal {
protected:
  SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
                                    // animal to be drawn, also non-owning
  SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use
                           // load_surface_for
  // todo: Attribute(s) to define its position
  SDL_Rect position_;

public:
  animal(const std::string& file_path, SDL_Surface* window_surface_ptr);
  // todo: The constructor has to load the sdl_surface that corresponds to the
  // texture

  ~animal(); // todo: Use the destructor to release memory and "clean up
               // behind you"

  void draw(); // todo: Draw the animal on the screen <-> window_surface_ptr.
                 // Note that this function is not virtual, it does not depend
                 // on the static type of the instance

  virtual void move() = 0; // todo: Animals move around, but in a different
                             // fashion depending on which type of animal
};

// Insert here:
// class sheep, derived from animal
class sheep : public animal {
  // todo
private:

  SDL_Surface* window_surface_ptr_;
  SDL_Surface* image_ptr_;

public:
  // Ctor
  sheep(SDL_Surface* window_surface_ptr);


  // Dtor
  ~sheep();
  // implement functions that are purely virtual in base class
  void move();
  void draw();

};

// Insert here:
// class wolf, derived from animal
// Use only sheep at first. Once the application works
// for sheep you can add the wolves

// The "ground" on which all the animals live (like the std::vector
// in the zoo example).


class ground {
private:
  // Attention, NON-OWNING ptr, again to the screen
  SDL_Surface* window_surface_ptr_;

  // Some attribute to store all the wolves and sheep
  // here
  std::vector<animal*> animals;


public:
  ground(SDL_Surface* window_surface_ptr)
      : 
      window_surface_ptr_{window_surface_ptr} {}; // todo: Ctor

  ~ground() {
    SDL_FreeSurface(window_surface_ptr_);
  }; // todo: Dtor, again for clean up (if necessary)

  void add_animal(animal* animal)
  {
      animals.push_back(animal);
  }; // todo: Add an animal


  void update(){
    for (int i = 0; i<animals.size();i++) {
    animals.at(i)->move();
      animals.at(i)->draw();
      
    }
  }; // todo: "refresh the screen": Move animals and draw them
  // Possibly other methods, depends on your implementation
};

// The application class, which is in charge of generating the window
class application {
private:
  // The following are OWNING ptrs
  SDL_Window* window_ptr_;
  SDL_Surface* window_surface_ptr_;
  SDL_Event window_event_;
  unsigned n_sheep_;
  // Other attributes here, for example an instance of ground
  ground ground_app_;

public:
  application(unsigned n_sheep, unsigned n_wolf)
      : window_ptr_{SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED, frame_width,
                                     frame_height,
                                     SDL_WINDOW_OPENGL)},
       window_surface_ptr_{SDL_GetWindowSurface(window_ptr_)}, 
       window_event_{},
       ground_app_{ground(window_surface_ptr_)}
      //, 
       //n_sheep_{n_sheep}
      {}; // Ctor


  ~application() {
    SDL_DestroyWindow(window_ptr_);
    SDL_FreeSurface(window_surface_ptr_);
  };    // dtor

  int loop(unsigned period) {
    SDL_FillRect(window_surface_ptr_, NULL, 888);

    //for (int i = 0; i < n_sheep_; i++) {
      sheep Sheep1 = sheep(window_surface_ptr_);
      ground_app_.add_animal(&Sheep1);
    //}

    int current_time=SDL_GetTicks();
    int last_time;
    while (current_time <period) 
    {
      last_time = SDL_GetTicks();
      std::cout << "last_time: "<< last_time << std::endl;

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
  }; // main loop of the application.
                             // this ensures that the screen is updated
                             // at the correct rate.
                             // See SDL_GetTicks() and SDL_Delay() to enforce a
                             // duration the application should terminate after
                             // 'period' seconds
};
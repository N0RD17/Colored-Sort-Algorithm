#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <random>
#include <ranges>
#include <vector>
#include <algorithm>


bool setGreen = false;

// Visualizes the step of the algorithm at every state
void draw_state(std::vector<int>& v, SDL_Renderer* renderer,
                unsigned int red_line, unsigned int blue_line)
{
   // Keeps tract of x-coord start and end
   unsigned int index = 0;

   for(const int& i : v)
   {
      if(index == red_line)
      {
         SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
      } else if (index == blue_line){
         SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
      } else {
         SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
      }
      // Draw line beginning at x-coord of index and y-coord of 99
      // End point of x-coord will be index and end of y-coord will be i
      SDL_RenderDrawLine(renderer, index, 99, index, i);
      // After finishing drawing line increment index
      index += 1;
   }
}


// Handles the sort turning green
void draw_Green(std::vector<int>& v, SDL_Renderer* renderer, unsigned int g_value)
{
   // The green index
   unsigned int gIndex = 0;

   
   for(const int &i : v)
   {

      // If a number is not part of gIndex then color it green
      if(g_value != gIndex)
      {
         SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
      } else {	// Else white
         SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      }

      // Draw the line
      SDL_RenderDrawLine(renderer, gIndex, 99,gIndex, i);
      gIndex += 1;	// Increment gIndex
   }
}

int main()
{
   // True random number generator
   std::random_device rd;
   // Generate numbers from 1 to 99
   std::uniform_int_distribution<int> d(1, 99);

   
   std::vector<int> v;

   // Gives v random numbers
   for(int i = 0; i < 100; i++)
   {
      v.push_back(d(rd));
   }

   // Handles Window and renderer creation
   SDL_Window* window = nullptr;
   SDL_Renderer* renderer = nullptr;

   SDL_CreateWindowAndRenderer(800, 600, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &window, &renderer);

   // Scales the Renderer to match the width and height of the Window
   SDL_RenderSetScale(renderer, 8, 6);
   
   // sort algorithm
   for(unsigned int i = 0; i < v.size(); i++)
   {
      for(unsigned int j = i; j < v.size(); j++)
      {
         if(v[j] < v[i])
         {
            std::swap(v[j], v[i]);
         }
         // Clear screen
         SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
         SDL_RenderClear(renderer);
         // Draw
         draw_state(v, renderer, i, j);
         // Display
         SDL_RenderPresent(renderer);
         // Slows it down for our eyes
         SDL_Delay(2);
      }
   }

   // Scan green
   for(unsigned int i = 0; i < v.size(); i++)
   {
      // Draws green
      draw_Green(v, renderer, i);
      SDL_RenderPresent(renderer);
      SDL_Delay(4);	// Slows it down for our eyes
   }

   

   // Displays the sorted numbers
   std::for_each(v.begin(), v.end(), [](int x){std::cout << x << " ";});

   // Checks if vector is sorted
   /* REQUIRES C++20
    * To RUN in your compiler enable C++20
    * OR if using terminal set your g++ flag to -std=c++20
   if(std::ranges::is_sorted(v))
   {
      std::cout << "\nsorted\n";
   }
   */

   std::cout << std::endl;

   // Desotrys Windows and Renderer then exit SDL2
   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(renderer);
   SDL_Quit();
   
   
   return 0;
}

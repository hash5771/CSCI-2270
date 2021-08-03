#ifndef MOVIETREE_HPP
#define MOVIETREE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

struct MovieNode {
    int ranking;
    string title;
    int year;
    float rating;
    MovieNode* left = NULL;
    MovieNode* right = NULL;
};

class MovieTree{
    private:
        MovieNode* root;
    public:
        MovieTree();
        ~MovieTree();
        void printMovieInventory();
        void addMovieNode(int ranking, std::string title, int year, float rating);
        void findMovie(string title);
        void queryMovies(float rating, int year);
        void averageRating();
        void printLevelNodes(int level);
};

#endif
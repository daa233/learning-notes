#include <vector>
#include <map>
#include <list>
#include <set>
#include <string>
#include <iostream>
#include <iomanip>
#include "imdb.h"
#include "path.h"
using namespace std;

/**
 * Using the specified prompt, requests that the user supply
 * the name of an actor or actress.  The code returns
 * once the user has supplied a name for which some record within
 * the referenced imdb existsif (or if the user just hits return,
 * which is a signal that the empty string should just be returned.)
 *
 * @param prompt the text that should be used for the meaningful
 *               part of the user prompt.
 * @param db a reference to the imdb which can be used to confirm
 *           that a user's response is a legitimate one.
 * @return the name of the user-supplied actor or actress, or the
 *         empty string.
 */

static string promptForActor(const string& prompt, const imdb& db,
                             short &creditsNum)
{
  string response;
  while (true) {
    cout << prompt << " [or <enter> to quit]: ";
    getline(cin, response);
    if (response == "") return "";
    vector<film> credits;
    if (db.getCreditsNum(response, creditsNum)) return response;
    cout << "We couldn't find \"" << response << "\" in the movie database. "
	 << "Please try again." << endl;
  }
}

/**
 * Get the credits of a given player. If the player's credits are already
 * in cache, return the credits in cache directly; else search in the imdb
 * and cache the result.
 * 
 * @param db a const reference to the imdb that should queried.
 * @param player the name of the actor or actresses being queried.
 * @param films a reference to the vector of films that should be updated
 *            with the list of the specified actor/actress's credits.
 * @param creditsCache a reference to the credits cache
 */

void getCredits(const imdb &db, const string &player,
                vector<film> &films,
                map<string, vector<film>> &creditsCache)
{
  // search the player's credits in the cache
  map<string, vector<film>>::const_iterator it;
  it = creditsCache.find(player);
  if (it != creditsCache.end()) {
    // already in cache
    films = it->second;
  } else {
    // not in cache
    db.getCredits(player, films);
    // now cache it
    creditsCache.insert(pair<string, vector<film>>(player, films));
  }
}

/**
 * Get the cast of a given film. If the film's cast are already in cache,
 * return the cast in cache directly; else search in the imdb and cache the
 * result.
 * 
 * @param db a const reference to the imdb that should queried.
 * @param movie an instance of film being queried.
 * @param players a reference to the vector of strings to be updated with the
 *                the list of actors and actresses starring in the specified
 *                film.
 * @param castCache a reference to the cast cache
 */

void getCast(const imdb &db, const film &movie,
             vector<string> &players,
             map<film, vector<string>> &castCache)
{
  // search the cast in the cache
  map<film, vector<string>>::const_iterator it;
  it = castCache.find(movie);
  if (it != castCache.end()) {
    // already in cache
    players = it->second;
  } else {
    // not in cache
    db.getCast(movie, players);
    // now cache it
    castCache.insert(pair<film, vector<string>>(movie, players));
  }
}


/**
 * Serves as the main entry point for the six-degrees executable.
 * There are no parameters to speak of.
 *
 * @param argc the number of tokens passed to the command line to
 *             invoke this executable.  It's completely ignored
 *             here, because we don't expect any arguments.
 * @param argv the C strings making up the full command line.
 *             We expect argv[0] to be logically equivalent to
 *             "six-degrees" (or whatever absolute path was used to
 *             invoke the program), but otherwise these are ignored
 *             as well.
 * @return 0 if the program ends normally, and undefined otherwise.
 */

int main(int argc, const char *argv[])
{
  imdb db(determinePathToData(argv[1])); // inlined in imdb-utils.h
  if (!db.good()) {
    cout << "Failed to properly initialize the imdb database." << endl;
    cout << "Please check to make sure the source files exist and that you have permission to read them." << endl;
    exit(1);
  }
  
  while (true) {
    short sourceCreditsNum = 0;
    short targetCreditsNum = 0;
    string source = promptForActor("Actor or actress", db, sourceCreditsNum);
    if (source == "") break;
    string target = promptForActor("Another actor or actress", db, targetCreditsNum);
    if (target == "") break;
    if (source == target) {
      cout << "Good one.  This is only interesting if you specify two different people." << endl;
    } else {
      // replace the following line by a call to your generateShortestPath routine... 
      int maxDegrees = 6;
      bool found = false;
      bool reverse = false;
      map<string, vector<film>> creditsCache;
      map<film, vector<string>> castCache;
      path shortestPath{source};

      // search from the actor with the smaller number of movies
      if (sourceCreditsNum > targetCreditsNum) {
        // swap the value of source and target
        string temp = source;
        source = target;
        target = temp;
        reverse = true;
      }

      /*
       * Breadth-First Search
       */
      list<path> pathList{shortestPath};  // init the list

      while (!pathList.empty() && !found) {
        path p = pathList.front();
        pathList.pop_front();
        
        // search the target in all the costars of the player
        string player = p.getLastPlayer();
        vector<film> films;
        getCredits(db, player, films, creditsCache);
        if (!films.empty()) {
          for (auto f : films) {
            if (found)  break;
            vector<string> players;
            getCast(db, f, players, castCache);
            if (!players.empty()) {
              for (auto player : players) {
                if (found) break;
                if (p.contain(player)) {
                  continue;
                }
                path newPath = p;
                newPath.addConnection(f, player);
                if (newPath.getLength() > maxDegrees) {
                  continue;
                } else {
                  if (player == target) {
                    // found the path
                    found = true;
                    shortestPath = newPath;
                    break;
                  } else {
                    // add new path to the pathList
                    pathList.push_back(newPath);
                  }
                }
              }
            }
          }
        }
      }

      if (reverse)
        shortestPath.reverse();

      if (found)
        cout << shortestPath << endl;
      else
        cout << endl << "No path between those two people could be found." << endl << endl;
    }
  }
  
  cout << "Thanks for playing!" << endl;
  return 0;
}


using namespace std;
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "imdb.h"

const char *const imdb::kActorFileName = "actordata";
const char *const imdb::kMovieFileName = "moviedata";

imdb::imdb(const string& directory)
{
  const string actorFileName = directory + "/" + kActorFileName;
  const string movieFileName = directory + "/" + kMovieFileName;
  
  actorFile = acquireFileMap(actorFileName, actorInfo);
  movieFile = acquireFileMap(movieFileName, movieInfo);
}

bool imdb::good() const
{
  return !( (actorInfo.fd == -1) || 
	    (movieInfo.fd == -1) ); 
}

int ActorCmp(const void *elem1, const void *elem2)
{
  ActorKey *key = (ActorKey *)elem1;
  int offset = *(int *)elem2;
  string actorName;
  parseActorRecord(key->actorFile, offset, &actorName, NULL, NULL, NULL);
  return key->player.compare(actorName);
}

int MovieCmp(const void *elem1, const void *elem2)
{
  MovieKey *key = (MovieKey *)elem1;
  int offset = *(int *)elem2;
  string title;
  int year;
  parseMovieRecord(key->movieFile, offset, &title, &year, NULL, NULL, NULL);
  film elemFilm{title, year};
  if (key->movie == elemFilm) {
    return 0;
  } else if (key->movie < elemFilm) {
    return -1;
  } else {
    return 1;
  }
}

void parseActorRecord(const void *actorFile, int playerOffset,
                      string *pPlayer, short *pNumCredits,
                      const void *movieFile, vector<film> *pFilms)
{
  void *playerRecord = (char *)actorFile + playerOffset;
  string player = string((char *)playerRecord);

  if (pPlayer != NULL) {
    *pPlayer = player;
  }

  if (pNumCredits == NULL && pFilms == NULL) { return; }

  int creditsNumOffset;
  if (player.length() % 2 == 0) {
    // padding an extra '\0' to make the length even
    creditsNumOffset = player.length() + 2;
  } else {
    creditsNumOffset = player.length() + 1;
  }
  int creditsOffset;
  if ((creditsNumOffset + 2) % 4 != 0) {
    // padding two extra '\0' to make the length a multiple of 4
    creditsOffset = creditsNumOffset + 4;
  } else {
    creditsOffset = creditsNumOffset + 2;
  }
  int numCredits = *(short *)((char *)playerRecord + creditsNumOffset);
  if (pNumCredits != NULL) {
    *pNumCredits = numCredits;
  }
  
  if (pFilms != NULL) {
    for (short i = 0; i < numCredits; ++i) {
      int movieOffset = *(int *)((char *)playerRecord + creditsOffset + i * 4);
      string title;
      int year;
      parseMovieRecord(movieFile, movieOffset, &title, &year,
                       NULL, NULL, NULL);
      film movie{title, year};
      (*pFilms).push_back(movie);
    }
  }
}

void parseMovieRecord(const void *movieFile, int movieOffset,
                      string *pTitle, int *pYear, short *pNumPlayers,
                      const void *actorFile, vector<string> *pPlayers)
{
  void *movieRecord = (char *)movieFile + movieOffset;
  string title = string((char *)movieRecord);

  if (pTitle != NULL) {
    *pTitle = title;
  }

  if (pYear != NULL) {
    *pYear = (int)*((char *)movieRecord + title.length() + 1) + 1900;
  }

  if (pNumPlayers == NULL && pPlayers == NULL) { return; }

  int playersNumOffset;
  if ((title.length() + 2) % 2 != 0) {
    // padding an extra '\0' after the year field
    playersNumOffset = title.length() + 2 + 1;
  } else {
    playersNumOffset = title.length() + 2;
  }
  int playersOffset;
  if ((playersNumOffset + 2) % 4 != 0) {
    // padding with extra zeros
    playersOffset = playersNumOffset + 4;
  } else {
    playersOffset = playersNumOffset + 2;
  }

  short numPlayers = *(short *)((char *)movieRecord + playersNumOffset);

  if (pNumPlayers != NULL) {
    *pNumPlayers = numPlayers;
  }

  if (pPlayers != NULL) {
    for (short i = 0; i < numPlayers; ++i) {
      int playerOffset = *(int *)((char *)movieRecord + playersOffset + i * 4);
      string player;
      parseActorRecord(actorFile, playerOffset, &player, NULL, NULL, NULL);
      (*pPlayers).push_back(player);
    }
  }
}

// you should be implementing these two methods right here... 
bool imdb::getCredits(const string& player, vector<film>& films) const
{
  // binary search the player in the actorFile
  int numActor = *(int *) actorFile;
  int playerOffset = 0;

  // use my own implementation of binary search
  // int left = 1;
  // int right = numActor;
  // int mid;
  // while (left <= right) {
  //   mid = (left + right) / 2;
  //   int offset = *((int *)actorFile + mid);
  //   void *actorRecord = (char *)actorFile + offset;
  //   string actorName = (char *)actorRecord;
  //   int compareResult = actorName.compare(player);
  //   if (compareResult < 0) {
  //     left = mid + 1;
  //   } else if (compareResult > 0) {
  //     right = mid - 1;
  //   } else {
  //     playerOffset = offset;
  //     break;
  //   }
  // }

  // use the binary search in the standard library
  ActorKey actorKey{player, actorFile};
  void *offsetActorFile = (void *)((int *)actorFile + 1);
  void *elemAddr = bsearch(&actorKey, offsetActorFile, numActor, sizeof(int),
                           ActorCmp);
  playerOffset = *(int *)elemAddr;

  if (playerOffset > 0) {
    parseActorRecord(actorFile, playerOffset, NULL, NULL, movieFile, &films);
    return true;
  }

  return false;
}

bool imdb::getCreditsNum(const string& player, short &num) const
{
  // binary search the player in the actorFile
  int numActor = *(int *) actorFile;
  int playerOffset = 0;
  // use the binary search in the standard library
  ActorKey actorKey{player, actorFile};
  void *offsetActorFile = (void *)((int *)actorFile + 1);
  void *elemAddr = bsearch(&actorKey, offsetActorFile, numActor, sizeof(int),
                           ActorCmp);
  playerOffset = *(int *)elemAddr;

  if (playerOffset > 0) {
    parseActorRecord(actorFile, playerOffset, NULL, &num, NULL, NULL);
    return true;
  }

  return false;
}

bool imdb::getCast(const film& movie, vector<string>& players) const
{
  // binary search the movie in the movieFile
  int numFilms = *(int *) movieFile;
  int movieOffset = 0;

  // use the binary search in the standard library
  MovieKey movieKey{movie, movieFile};
  void *offsetMovieFile = (void *)((int *)movieFile + 1);
  void *elemAddr = bsearch(&movieKey, offsetMovieFile, numFilms, sizeof(int),
                           MovieCmp);
  movieOffset = *(int *)elemAddr;

  if (movieOffset > 0) {
    parseMovieRecord(movieFile, movieOffset, NULL, NULL, NULL,
                     actorFile, &players);
    return true;
  }
  
  return false;
}

imdb::~imdb()
{
  releaseFileMap(actorInfo);
  releaseFileMap(movieInfo);
}

// ignore everything below... it's all UNIXy stuff in place to make a file look like
// an array of bytes in RAM.. 
const void *imdb::acquireFileMap(const string& fileName, struct fileInfo& info)
{
  struct stat stats;
  stat(fileName.c_str(), &stats);
  info.fileSize = stats.st_size;
  info.fd = open(fileName.c_str(), O_RDONLY);
  return info.fileMap = mmap(0, info.fileSize, PROT_READ, MAP_SHARED, info.fd, 0);
}

void imdb::releaseFileMap(struct fileInfo& info)
{
  if (info.fileMap != NULL) munmap((char *) info.fileMap, info.fileSize);
  if (info.fd != -1) close(info.fd);
}

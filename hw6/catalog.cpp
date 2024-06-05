#include "catalog.h"

using namespace std;

template class Catalog<Movie>;
template class Catalog<Music>;
template class Catalog<Book>;


template <class T>
void Catalog<T> :: readDataFile(const string& filename)
{
    ifstream file(filename);

    if (!file.is_open()) 
    {
        cerr << "Can not open file: " << filename << endl;
        exit(1);
    }

    string line;
    getline(file,line); // "movie" satırını atla

    ofstream tempFile("temp.txt");
    ofstream outputFile("outputs.txt");

    if (!tempFile.is_open() || !outputFile.is_open()) 
    {
        cerr << "Can not create temp.txt or outputs.txt" << endl;
        file.close();
        exit(1);
    }

    if constexpr (is_same_v<T, Movie>)
    {
        outputFile << "Catalog Read: movie" << endl;

        while (getline(file,line)) 
        {            
            stringstream ss(line);
            vector<string> tokens;
            string token;

            while (getline(ss,token,'"')) 
            {
                if (!token.empty() && token != " ")
                {
                    tokens.push_back(token);
                }
            }

            int actualSize = count_if(tokens.begin(), tokens.end(), [](const string& t) 
            {
                return !t.empty() && t != "";
            });

            if (actualSize != 5)
            {
                outputFile << "Exception: missing field" << endl;
                outputFile << line << endl;
                continue;
            }

            string title = tokens[0];
            string director = tokens[1];
            int year = stoi(tokens[2]);

            vector<string> genres;
            stringstream genreSS(tokens[3]);

            while (getline(genreSS,token,',')) 
            {
                genres.push_back(token);
            }

            vector<string> starring;
            stringstream starringSS(tokens[4]);

            while (getline(starringSS,token,',')) 
            {
                starring.push_back(token);
            }
            bool duplicateEntry = false;

            for (const T& item : items) 
            {
                if (item.getTitle() == title /*&& movie.getDirector() == director && movie.getYear() == year && movie.getGenres() == genres && movie.getStarring() == starring*/) 
                {
                    outputFile << "Exception: duplicate entry" << endl;
                    outputFile << line << endl;
                    duplicateEntry = true;
                    break;
                }
            }

            if (!duplicateEntry) 
            {
                Movie movie(title,director,year,genres,starring);
                items.push_back(movie);

                tempFile << line << endl;
            }
        }
    }

    else if constexpr(is_same_v<T,Book>)
    {
        outputFile << "Catalog Read: book" << endl;

        while (getline(file,line)) 
        {
            stringstream ss(line);
            vector<string> tokens;
            string token;

            while (getline(ss,token,'"')) 
            {
                if (!token.empty() && token != " ")
                {
                    tokens.push_back(token);
                }
            }

            int actualSize = count_if(tokens.begin(), tokens.end(), [](const string& t) 
            {
                return !t.empty() && t != "";
            });

            if (actualSize != 4)
            {
                outputFile << "Exception: missing field" << endl;
                outputFile << line << endl;
                continue;
            }

            string title = tokens[0];

            vector<string> authors;
            stringstream authorSS(tokens[1]);

            while (getline(authorSS,token,','))
            {
                authors.push_back(token);
            }
            int year = stoi(tokens[2]);

            vector<string> tags;
            stringstream tagSS(tokens[3]);

            while (getline(tagSS,token,',')) 
            {
                tags.push_back(token);
            }
            bool duplicateEntry = false;

            for (const T& item : items) 
            {
                if (item.getTitle() == title /*&& movie.getDirector() == director && movie.getYear() == year && movie.getGenres() == genres && movie.getStarring() == starring*/) 
                {
                    outputFile << "Exception: duplicate entry" << endl;
                    outputFile << line << endl;
                    duplicateEntry = true;
                    break;
                }
            }

            if (!duplicateEntry) 
            {
                Book book(year,title,authors,tags);
                items.push_back(book);

                tempFile << line << endl;
            }
        }
    }

    else if constexpr(is_same_v<T,Music>)
    {
        outputFile << "Catalog Read: music" << endl;

        while (getline(file,line)) 
        {
            stringstream ss(line);
            vector<string> tokens;
            string token;

            while (getline(ss,token,'"')) 
            {
                if (!token.empty() && token != " ")
                {
                    tokens.push_back(token);
                }
            }

            int actualSize = count_if(tokens.begin(), tokens.end(), [](const string& t) 
            {
                return !t.empty() && t != "";
            });

            if (actualSize != 4)
            {
                outputFile << "Exception: missing field" << endl;
                outputFile << line << endl;
                continue;
            }

            string title = tokens[0];

            vector<string> artists;
            stringstream artistSS(tokens[1]);

            while (getline(artistSS,token,','))
            {
                artists.push_back(token);
            }
            int year = stoi(tokens[2]);

            vector<string> genres;
            stringstream genreSS(tokens[3]);

            while (getline(genreSS,token,',')) 
            {
                genres.push_back(token);
            }
            bool duplicateEntry = false;

            for (const T& item : items) 
            {
                if (item.getTitle() == title /*&& movie.getDirector() == director && movie.getYear() == year && movie.getGenres() == genres && movie.getStarring() == starring*/) 
                {
                    outputFile << "Exception: duplicate entry" << endl;
                    outputFile << line << endl;
                    duplicateEntry = true;
                    break;
                }
            }

            if (!duplicateEntry) 
            {
                Music music(year,title,artists,genres);
                items.push_back(music);

                tempFile << line << endl;
            }
        }
    }
    file.close();
    tempFile.close();
    outputFile.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
}

template <class T>
void Catalog<T>::processCommands(const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Cannot open file: " << filename << endl;
        exit(1);
    }

    string line;
    ofstream outputFile("outputs.txt");

    int uniqueEntryCount = items.size();
    outputFile << uniqueEntryCount << " unique entries" << endl;

    while (getline(file, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "sort")
        {
            string field;
            ss >> field;

            field = field.substr(1, field.length() - 2); // Remove quotation marks

            if (field == "title")
            {
                sort(items.begin(), items.end(), [](const T& a, const T& b) 
                {
                    return a.getTitle() < b.getTitle();
                });
            }

            else if (field == "year")
            {
                sort(items.begin(), items.end(), [](const T& a, const T& b) 
                {
                    return a.getYear() < b.getYear();
                });
            }
            else
            {
                outputFile << "Exception: command is wrong" << endl;
                outputFile << line << endl;
            }
        }

        else if (command == "search")
        {
            string searchString, inField;

            ss >> searchString >> inField;

            inField = inField.substr(1, inField.length() - 2); // Remove quotation marks

            vector<T> searchResults;

            if constexpr (is_same_v<T, Movie>)
            {
                if (inField == "title")
                {
                    for (const T& item : items)
                    {
                        if (item.getTitle().find(searchString) != string::npos)
                        {
                            searchResults.push_back(item);
                        }
                    }
                }

                else if (inField == "director")
                {
                    for (const T& item : items)
                    {
                        if (item.getDirector().find(searchString) != string::npos)
                        {
                            searchResults.push_back(item);
                        }
                    }
                }

                else if (inField == "year")
                {
                    int searchYear = stoi(searchString);

                    for (const T& item : items)
                    {
                        if (item.getYear() == searchYear)
                        {
                            searchResults.push_back(item);
                        }
                    }
                }

                else if (inField == "genre")
                {
                    for (const T& item : items)
                    {
                        const vector<string>& genres = item.getGenres();

                        for (const string& genre : genres)
                        {
                            if (genre.find(searchString) != string::npos)
                            {
                                searchResults.push_back(item);
                                break;
                            }
                        }
                    }
                }

                else if (inField == "starring")
                {
                    for (const T& item : items)
                    {
                        const vector<string>& starring = item.getStarring();

                        for (const string& star : starring)
                        {
                            if (star.find(searchString) != string::npos)
                            {
                                searchResults.push_back(item);
                                break;
                            }
                        }
                    }
                }

                else
                {
                    outputFile << "Exception: command is wrong" << endl;
                    outputFile << line << endl;
                }
            }

            else if constexpr (is_same_v<T, Music>)
            {
                if (inField == "title")
                {
                    for (const T& item : items)
                    {
                        if (item.getTitle().find(searchString) != string::npos)
                        {
                            searchResults.push_back(item);
                        }
                    }
                }

                else if (inField == "artists")
                {
                    for (const T& item : items)
                    {
                        const vector<string>& artists = item.getArtists();

                        for (const string& artist : artists)
                        {
                            if (artist.find(searchString) != string::npos)
                            {
                                searchResults.push_back(item);
                                break;
                            }
                        }
                    }
                }

                else if (inField == "year")
                {
                    int searchYear = stoi(searchString);

                    for (const T& item : items)
                    {
                        if (item.getYear() == searchYear)
                        {
                            searchResults.push_back(item);
                        }
                    }
                }

                else if (inField == "genre")
                {
                    for (const T& item : items)
                    {
                        const vector<string>& genres = item.getGenres();

                        for (const string& genre : genres)
                        {
                            if (genre.find(searchString) != string::npos)
                            {
                                searchResults.push_back(item);
                                break;
                            }
                        }
                    }
                }

                else
                {
                    outputFile << "Exception: command is wrong" << endl;
                    outputFile << line << endl;
                }
            }

            else if constexpr (is_same_v<T, Book>)
            {
                if (inField == "title")
                {
                    for (const T& item : items)
                    {
                        if (item.getTitle().find(searchString) != string::npos)
                        {
                            searchResults.push_back(item);
                        }
                    }
                }

                else if (inField == "authors")
                {
                    for (const T& item : items)
                    {
                        const vector<string>& authors = item.getAuthors();

                        for (const string& author : authors)
                        {
                            if (author.find(searchString) != string::npos)
                            {
                                searchResults.push_back(item);
                                break;
                            }
                        }
                    }
                }

                else if (inField == "year")
                {
                    int searchYear = stoi(searchString);

                    for (const T& item : items)
                    {
                        if (item.getYear() == searchYear)
                        {
                            searchResults.push_back(item);
                        }
                    }
                }

                else if (inField == "tags")
                {
                    for (const T& item : items)
                    {
                        const vector<string>& tags = item.getTags();

                        for (const string& tag : tags)
                        {
                            if (tag.find(searchString) != string::npos)
                            {
                                searchResults.push_back(item);
                                break;
                            }
                        }
                    }
                }

                else
                {
                    outputFile << "Exception: command is wrong" << endl;
                    outputFile << line << endl;
                }
            }
            outputFile << line << endl;

            for (const T& item : searchResults)
            {
                outputFile << item.getTitle() << " ";

                if constexpr (is_same_v<T, Movie>)
                {
                    outputFile << item.getDirector() << " ";
                }

                else if constexpr (is_same_v<T, Music>)
                {
                    const vector<string>& artists = item.getArtists();

                    for (int i = 0; i < artists.size(); ++i)
                    {
                        outputFile << artists[i];

                        if (i != artists.size() - 1)
                        {
                            outputFile << ", ";
                        }
                    }
                    outputFile << " ";
                }

                else if constexpr (is_same_v<T, Book>)
                {
                    const vector<string>& authors = item.getAuthors();

                    for (int i = 0; i < authors.size(); ++i)
                    {
                        outputFile << authors[i];

                        if (i != authors.size() - 1)
                        {
                            outputFile << ", ";
                        }
                    }
                    outputFile << " ";
                }

                outputFile << item.getYear() << " ";

                if constexpr (is_same_v<T, Book>)
                {
                    const vector<string>& tags = item.getTags();

                    for (int i = 0; i < tags.size(); ++i)
                    {
                        outputFile << tags[i];

                        if (i != tags.size() - 1)
                        {
                            outputFile << ", ";
                        }
                    }
                    outputFile << " ";
                }

                else if constexpr (is_same_v<T, Music>)
                {
                    const vector<string>& genres = item.getGenres();

                    for (int i = 0; i < genres.size(); ++i)
                    {
                        outputFile << genres[i];

                        if (i != genres.size() - 1)
                        {
                            outputFile << ", ";
                        }
                    }
                    outputFile << " ";
                }

                else if constexpr (is_same_v<T, Movie>)
                {
                    const vector<string>& genres = item.getGenres();

                    for (int i = 0; i < genres.size(); ++i)
                    {
                        outputFile << genres[i];

                        if (i != genres.size() - 1)
                        {
                            outputFile << ", ";
                        }
                    }
                    outputFile << " ";

                    const vector<string>& starrings = item.getStarring();

                    for (int i = 0; i < starrings.size(); ++i)
                    {
                        outputFile << starrings[i];

                        if (i != starrings.size() - 1)
                        {
                            outputFile << ", ";
                        }
                    }
                    outputFile << " ";
                }
                outputFile << endl;
            }
            outputFile << "Found " << searchResults.size() << " results" << endl;
        }

        else
        {
            outputFile << "Exception: command is wrong" << endl;
            outputFile << line << endl;
        }
    }
    file.close();
    outputFile.close();
}
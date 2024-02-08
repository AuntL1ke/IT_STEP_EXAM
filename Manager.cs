using System;
using System.Collections.Generic;
using System.IO;
using Newtonsoft.Json;

namespace MyProgram
{
    class Manager
    {
        public Dictionary<string, CustomDictionary> dictionaries;
        private string dataDirectory = "data";

        public Manager()
        {
            dictionaries = new Dictionary<string, CustomDictionary>();
        }

        public void Run()
        {

            if (!Directory.Exists(dataDirectory))
            {
                Directory.CreateDirectory(dataDirectory);
            }

            bool exit = false;
            while (!exit)
            {

                Console.WriteLine("Enter command:\n1 - Create Dictionary\n2 - Add Word Translation\n3 - Replace Word\n4 - Replace Translation\n5 - Delete Word\n6 - Delete Translation\n7 - Search Translation\n8 - Save Data\n9 - Load Data\n0 - Exit\n");

                int option;
                if (int.TryParse(Console.ReadLine(), out option))
                {
                    switch (option)
                    {
                        case 1:
                            CreateDict();
                            break;
                        case 2:
                            AddWordTranslation();
                            break;
                        case 3:
                            ReplaceWord();
                            break;
                        case 4:
                            ReplaceTranslation();
                            break;
                        case 5:
                            DeleteWord();
                            break;
                        case 6:
                            DeleteTranslation();
                            break;
                        case 7:
                            SearchTranslation();
                            break;
                        case 8:
                            SaveData();
                            break;
                        case 9:
                            LoadData();
                            break;
                        case 0:
                            exit = true;
                            break;
                        default:
                            Console.WriteLine("Invalid option. Please try again.");
                            break;
                    }
                }
                else
                {
                    Console.WriteLine("Invalid option. Please try again.");
                }
            }
        }

        private void CreateDict()
        {
            Console.Write("Enter dictionary name: ");
            string dictName = Console.ReadLine();

            if (!dictionaries.ContainsKey(dictName))
            {
                dictionaries[dictName] = new CustomDictionary();
                Console.WriteLine($"Dictionary '{dictName}' created.");
            }
            else
            {
                Console.WriteLine("This dictionary already exists.");
            }
        }

        private void AddWordTranslation()
        {
            Console.Write("Enter dictionary name: ");
            string dictName = Console.ReadLine();

            if (dictionaries.ContainsKey(dictName))
            {
                dictionaries[dictName].AddWordTranslation();
            }
            else
            {
                Console.WriteLine("Dictionary not found.");
            }
        }

        private void ReplaceWord()
        {
            Console.Write("Enter dictionary name: ");
            string dictName = Console.ReadLine();

            if (dictionaries.ContainsKey(dictName))
            {
                dictionaries[dictName].ReplaceWord();
            }
            else
            {
                Console.WriteLine("Dictionary not found.");
            }
        }

        private void ReplaceTranslation()
        {
            Console.Write("Enter dictionary name: ");
            string dictName = Console.ReadLine();

            if (dictionaries.ContainsKey(dictName))
            {
                dictionaries[dictName].ReplaceTranslation();
            }
            else
            {
                Console.WriteLine("Dictionary not found.");
            }
        }

        private void DeleteWord()
        {
            Console.Write("Enter dictionary name: ");
            string dictName = Console.ReadLine();

            if (dictionaries.ContainsKey(dictName))
            {
                dictionaries[dictName].DeleteWord();
            }
            else
            {
                Console.WriteLine("Dictionary not found.");
            }
        }

        private void DeleteTranslation()
        {
            Console.Write("Enter dictionary name: ");
            string dictName = Console.ReadLine();

            if (dictionaries.ContainsKey(dictName))
            {
                dictionaries[dictName].DeleteTranslation();
            }
            else
            {
                Console.WriteLine("Dictionary not found.");
            }
        }

        private void SearchTranslation()
        {
            Console.Write("Enter dictionary name: ");
            string dictName = Console.ReadLine();

            if (dictionaries.ContainsKey(dictName))
            {
                Console.Write("Enter the word: ");
                string word = Console.ReadLine();
                if (dictionaries[dictName].Words.ContainsKey(word))
                {
                    Console.WriteLine("Translations:");
                    foreach (var translation in dictionaries[dictName].Words[word])
                    {
                        Console.WriteLine(translation);
                    }
                }
                else
                {
                    Console.WriteLine("Word not found in the dictionary.");
                }
            }
            else
            {
                Console.WriteLine("Dictionary not found.");
            }
        }

        private void SaveData()
        {
            string json = JsonConvert.SerializeObject(dictionaries, Formatting.Indented);
            File.WriteAllText(Path.Combine(dataDirectory, "data.json"), json);
            Console.WriteLine("Data saved successfully.");
        }

        private void LoadData()
        {
            string filePath = Path.Combine(dataDirectory, "data.json");
            if (File.Exists(filePath))
            {
                string json = File.ReadAllText(filePath);
                dictionaries = JsonConvert.DeserializeObject<Dictionary<string, CustomDictionary>>(json);
                Console.WriteLine("Data loaded successfully.");
            }
            else
            {
                Console.WriteLine("No saved data found.");
            }
        }
    }
}
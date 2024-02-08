using System;
using System.Collections.Generic;
using System.IO;
using Newtonsoft.Json;

namespace MyProgram
{
    class CustomDictionary
    {
        public Dictionary<string, List<string>> Words;

        public CustomDictionary()
        {
            Words = new Dictionary<string, List<string>>();
        }

        public void AddWordTranslation()
        {
            Console.Write("Enter the word: ");
            string word = Console.ReadLine();

            if (!Words.ContainsKey(word))
            {
                Words[word] = new List<string>();

                do
                {
                    Console.Write("Enter the translation: ");
                    Words[word].Add(Console.ReadLine());

                    Console.Write("Do you want to add one more translation? (yes/no): ");
                } while (Console.ReadLine().ToLower() == "yes");

                Console.WriteLine($"Word '{word}' added to the dictionary.");
            }
            else
            {
                Console.WriteLine("This word is already in the dictionary.");
            }
        }

        public void ReplaceWord()
        {
            Console.Write("Enter the word to replace: ");
            string oldWord = Console.ReadLine();
            if (Words.ContainsKey(oldWord))
            {
                Console.Write("Enter new word: ");
                string newWord = Console.ReadLine();
                Words[newWord] = Words[oldWord];
                Words.Remove(oldWord);
                Console.WriteLine($"Word '{oldWord}' replaced with '{newWord}'.");
            }
            else
            {
                Console.WriteLine("Word not found in the dictionary.");
            }
        }

        public void ReplaceTranslation()
        {
            Console.Write("Enter the word: ");
            string word = Console.ReadLine();
            if (Words.ContainsKey(word))
            {
                Console.Write("Enter translation to replace: ");
                string oldTranslation = Console.ReadLine();
                if (Words[word].Contains(oldTranslation))
                {
                    Console.Write("Enter new translation: ");
                    string newTranslation = Console.ReadLine();
                    int index = Words[word].IndexOf(oldTranslation);
                    Words[word][index] = newTranslation;
                    Console.WriteLine($"Translation '{oldTranslation}' replaced with '{newTranslation}' for word '{word}'.");
                }
                else
                {
                    Console.WriteLine("Translation not found.");
                }
            }
            else
            {
                Console.WriteLine("Word not found in the dictionary.");
            }
        }

        public void DeleteWord()
        {
            Console.Write("Enter word to delete: ");
            string word = Console.ReadLine();
            if (Words.ContainsKey(word))
            {
                Words.Remove(word);
                Console.WriteLine($"Word '{word}' deleted from the dictionary.");
            }
            else
            {
                Console.WriteLine("Word not found in the dictionary.");
            }
        }

        public void DeleteTranslation()
        {
            Console.Write("Enter the word: ");
            string word = Console.ReadLine();
            if (Words.ContainsKey(word))
            {
                Console.Write("Enter translation to delete: ");
                string translation = Console.ReadLine();
                if (Words[word].Contains(translation))
                {
                    Words[word].Remove(translation);
                    Console.WriteLine($"Translation '{translation}' deleted for word '{word}'.");
                }
                else
                {
                    Console.WriteLine("Translation not found for the word.");
                }
            }
            else
            {
                Console.WriteLine("Word not found in the dictionary.");
            }
        }
    }

}

// https://leetcode.com/problems/prefix-and-suffix-search/
// If we have n words, since words are of length at most 10,
// and f is going to be called at most n times, then
// algorithmicic complexity is O(n) and space consumption is O(n)
package main

import (
	"fmt"
)

type Pair struct {
	first string
	second string
}

type Trie map[string]int

func compute_trie(words []string) Trie {
	m := Trie{}

	for weight, word := range words {
		prefix := ""

		for j := 0; j <= len(word); j++ {
			suffix := ""

			for k := len(word) - 1; k >= 0; k-- {
				if k < len(word) {
					suffix = string(word[k]) + suffix
				}
				current := prefix + "#" + suffix
				if _, ok := m[current]; !ok {
					m[current] = weight + 1
				}
			}
			if j < len(word) {
				prefix = prefix + string(word[j])
			}
		}
	}

	return m
}

func f(m Trie, prefix string, suffix string) int {
	return m[prefix + "#" + suffix] - 1
}

func main() {
	words := []string{"apple", "otra"}
	queries := []Pair{Pair{"a", "e"}, Pair{"ota", "ra"}}
	m := compute_trie(words)
	for _, p := range queries {
		a := p.first
		b := p.second
		fmt.Println("Weight for " + a + ", " + b + " is:", f(m, a, b))
	}
}

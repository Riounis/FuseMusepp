/* 
 * File:   chordtest.cpp
 * Author: Sam Rappl
 *
 */

#include <vector>
#include "chord.h"
#include "constants.h"
#include "gtest/gtest.h"

TEST(chordTest, chordDefaultConstructorTest) {
	// Test Default constructor
	Chord chord;
	ASSERT_EQ(c_major_chord, chord.pitches);
	ASSERT_EQ(quarter_note, chord.duration);
	ASSERT_FALSE(chord.triplet);
	ASSERT_FALSE(chord.dotted);
	ASSERT_FALSE(chord.double_dotted);
	ASSERT_FALSE(chord.staccato);
	ASSERT_FALSE(chord.tenuto);
	ASSERT_FALSE(chord.accent);
	ASSERT_FALSE(chord.fermata);
	ASSERT_FALSE(chord.tied);
	ASSERT_FALSE(chord.slurred);
}

TEST(chordTest, chordConstructorPitchDurationTest) {
	// Test pitch and duration constructor
	Chord chord(d_major_chord, quarter_note);
	ASSERT_EQ(d_major_chord, chord.pitches);
	ASSERT_EQ(quarter_note, chord.duration);
	ASSERT_FALSE(chord.triplet);
	ASSERT_FALSE(chord.dotted);
	ASSERT_FALSE(chord.double_dotted);
	ASSERT_FALSE(chord.staccato);
	ASSERT_FALSE(chord.tenuto);
	ASSERT_FALSE(chord.accent);
	ASSERT_FALSE(chord.fermata);
	ASSERT_FALSE(chord.tied);
	ASSERT_FALSE(chord.slurred);
}

TEST(chordTest, chordConstructorPitchDurationTripDotDoubleTest) {
	Chord chord(d_major_chord, dotted_quarter_note, false, true, false);
	ASSERT_FALSE(chord.triplet);
	ASSERT_TRUE(chord.dotted);
	ASSERT_FALSE(chord.double_dotted);
}

TEST(chordTest, chordAllArgsConstructorTest) {
	// Test all argument constructor
	Chord chord(d_major_chord, quarter_note, false, false, false, true,
		false, false, false, false, true);
	ASSERT_EQ(d_major_chord, chord.pitches);
	ASSERT_EQ(quarter_note, chord.duration);
	ASSERT_FALSE(chord.triplet);
	ASSERT_FALSE(chord.dotted);
	ASSERT_FALSE(chord.double_dotted);
	ASSERT_TRUE(chord.staccato);
	ASSERT_FALSE(chord.tenuto);
	ASSERT_FALSE(chord.accent);
	ASSERT_FALSE(chord.fermata);
	ASSERT_FALSE(chord.tied);
	ASSERT_TRUE(chord.slurred);
}

TEST(chordTest, dotTest) {
	Chord chord(gs_minor_chord, quarter_note);
	
	// Test dot function
	chord.dot();
	ASSERT_EQ(dotted_quarter_note, chord.duration);
	
	// Test dotting a second time
	chord.dot();
	ASSERT_EQ(double_dotted_quarter_note, chord.duration);
	
	// Test dotting a third time
	ASSERT_FALSE(chord.dot());
	
	// Test double dotting
	Chord chord2(a_sus2_chord, quarter_note);
	chord2.double_dot();
	ASSERT_EQ(double_dotted_quarter_note, chord2.duration);
	
	// Test double dotting a dotted chord
	Chord chord3(e_minor_7_chord, dotted_quarter_note, false, true, false);
	ASSERT_FALSE(chord3.double_dot());
}

TEST(chordTest, tripletTest) {
	Chord chord(b_sus4_chord, quarter_note);
	Chord chord2(c_major_7_chord, dotted_eighth_note, false, true, false);
	Chord chord3(e_minor_chord, triplet_eighth_note, true, false, false);
	
	// Test put_in_triplet function
	chord.put_in_triplet();
	ASSERT_EQ(triplet_quarter_note, chord.duration);
	ASSERT_FALSE(chord.put_in_triplet());
	chord2.put_in_triplet();
	ASSERT_EQ(triplet_dotted_eighth_note, chord2.duration);
	ASSERT_FALSE(chord2.put_in_triplet());
	ASSERT_FALSE(chord3.put_in_triplet());
}

TEST(chordTest, addOctaveTest) {
	std::vector<int> invec;
	invec.push_back(c4);
	invec.push_back(e4);
	invec.push_back(g4);
	Chord chord;
	chord.add_octave();
	ASSERT_EQ(invec, chord.pitches);
	for (int i = 4; i < 9; i++) {
		ASSERT_TRUE(chord.add_octave());
	}
	ASSERT_FALSE(chord.add_octave());
}

TEST(chordTest, dropOctaveTest) {
	std::vector<int> invec;
	invec.push_back(c2);
	invec.push_back(e2);
	invec.push_back(g2);
	Chord chord;
	chord.drop_octave();
	ASSERT_EQ(invec, chord.pitches);
	for (int i = 2; i > 0; i--) {
		ASSERT_TRUE(chord.drop_octave());
	}
	ASSERT_FALSE(chord.drop_octave());
}

TEST(chordTest, inversionTest) {
	std::vector<int> invec;
	invec.push_back(e3);
	invec.push_back(g3);
	invec.push_back(c4);
	Chord chord;
	chord.invert();
	ASSERT_EQ(invec, chord.pitches);
	std::vector<int> invec2;
	invec2.push_back(c4);
	Chord chord2(invec2, quarter_note);
	ASSERT_FALSE(chord2.invert());
}

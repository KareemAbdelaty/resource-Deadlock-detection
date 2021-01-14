//Kareem Abdelaty
//30075331


// this is the ONLY file you should edit and submit to D2L

#include "common.h"
#include "deadlock_detector.h"
#include <iostream>

/// this is the function you need to implement
/// parameter edges[] contains a list of request and assignment edges
///   example of a request edge, process "p1" resource "r1"
///     "p1 -> r1"
///   example of an assignment edge, process "XYz" resource "XYz"
///     "XYz <- XYz"
/// Parameters edge_index and cycle[] are used to return
/// results back to the caller.
///
/// You need to process edges[] one edge at a time, and run a deadlock
/// detection after each edge.
///
/// As soon as you detecte a deadlock, you need to set edge_index to the index of the edge
/// in edges[] that caused the deadlock. For example, edges[7] caused the deadlock,
/// then set edge_index=7. You must also populete cycle[] with the names of
/// processes that are in a deadlock. You can then return from the function without
/// processing any other edges.
///
/// To indicate deadlock was detected after processing all edges, you must
/// set edge_index = -1 and clear cycle[] e.g. by calling cycle.clear()
///
/*class FastGraph {
	public:
		std::vector<std::vector<int>> adj_list;
		std::vector<int> out_counts;
};*/

void detect_deadlock(
    const std::vector<std::string> & edges,
    int & edge_index,
    std::vector<std::string> & cycle)
{	
	//intialise edge index and cycle to default
	edge_index =-1;
	cycle.clear();
	//intialise graph and node structures and word to int
//	FastGraph g = FastGraph();
	Word2Int w2i;
	std::unordered_map<int, std::string> wordToIntMap;
	unsigned long int into;
	unsigned long int outfrom;
	std::vector<int> out;
	std::vector<int> zeros;
	std::vector<std::vector<int>> adj_list(2);
	std::vector<int> out_counts(2);
	int index =0;
	//build adjancy list
	//while sorting after each edge
	for(std::string s : edges){
		std::vector<std::string> temp = split(s);
		temp[0].append("P");
		temp[2].append("R");
		if(temp[1] == "<-"){
			into = w2i.get(temp[0]);
			outfrom = w2i.get(temp[2]);
			wordToIntMap[into] = temp[0];
			wordToIntMap[outfrom] = temp[2];
			if((outfrom>=out_counts.size())||(into>=adj_list.size())){
				auto size = adj_list.size()+2;
				out_counts.resize(size);
				adj_list.resize(size);
			}
			adj_list[into].push_back(outfrom);
			out_counts[outfrom]++;
		}else{
			into = w2i.get(temp[2]);
			outfrom = w2i.get(temp[0]);
			wordToIntMap[into] = temp[2];
			wordToIntMap[outfrom] = temp[0];
			if((outfrom>=out_counts.size())||(into>=adj_list.size())){
				auto size = adj_list.size()+2;
				out_counts.resize(size);
				adj_list.resize(size);
			}
			adj_list[into].push_back(outfrom);
			out_counts[outfrom]++;
		}
		out = out_counts;
		for(unsigned long int i =0;i<out.size();i++){
			if(out[i] == 0){
				zeros.push_back(i);
			}
		}
		while (zeros.size() > 0){
			 int n = zeros.back();
			 zeros.pop_back();
			 for(auto n2 :adj_list[n]){
			   out[n2] --;
			   if(out[n2] == 0){
				   zeros.push_back(n2);
			   }
					
			 }
		}
		bool got_index = false;
		for(unsigned long int i =0;i<out.size();i++){
			if(out[i] > 0){
				std::string word = wordToIntMap[i];
				char end = word.back();
				if(end =='P'){
					if(!got_index){
						got_index =true;
						edge_index = index;
					}
					word.pop_back();
					cycle.push_back(word);
				}
			}
		}	
		index++;
		if(!cycle.empty()){
			break;
		}	
	}

}

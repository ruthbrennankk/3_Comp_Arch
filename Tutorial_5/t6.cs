using System; using System.Collections.Generic; using System.Linq;

namespace hitsAndMisses
{
    class hitsAndMisses
    {

	private static bool isHit(List<Dictionary<int,long>> cache, int nTags, int tag, int set )
        {

            if(cache[set].ContainsKey(tag))
            {
                cache[set][tag] = DateTime.Now.Ticks;
                return true;
            }
            else
            {
                if (cache[set].Count < nTags){cache[set][tag] = DateTime.Now.Ticks;}
                else 
		{
                    var k = cache[set].Aggregate((l, r) => l.Value < r.Value ? l : r).Key;
                    cache[set].Remove(k);
                    cache[set][tag] = DateTime.Now.Ticks;
                }
                
                return false;
            }
        }
	
        static void Main(string[] args)
        {
          //Sort out input
            string input = "0000 => 0004 => 000c => 2200 => 00d0 => 00e0 => 1130 => 0028 => 113c = > 2204 = > 0010 = > 0020 = > 0004 = > 0040 = > 2208 = > 0008 = > 00a0 = > 0004 = > 1104 = > 0028 = > 000c = > 0084 = > 000c = > 3390 = > 00b0 = > 1100 = > 0028 = > 0064 = > 0070 = > 00d0 = > 0008 = > 3394";

            List<string> replacedandsplit = input.Replace(" ", "").Split("=>").ToList();
            List<string> ready = new List<string>();

         //Clean up
            replacedandsplit.ForEach(item =>
            {
                int intermediary = Convert.ToInt32(item, 16);
                string binaryString = Convert.ToString(intermediary, 2).PadLeft(16, '0');
                ready.Add(binaryString);
            });


	//set up caches
            int[] ways = { 1, 2, 4, 8 };
            int[] bytes = { 128, 128, 128, 128 };
            int[] by_per_line = { 16, 16, 16, 16 };

	//work on caches
            for(int i=0; i < 4; i++)
            {
                int L = by_per_line[i];
                int N = bytes[i] / (by_per_line[i]*ways[i]);
                int K = ways[i];
 
                int offset = (int)Math.Log(L,2);
                int set = (int)(Math.Log(N, 2));
                int tag = L-offset-set;

                List<Dictionary<int, long>> cache = new List<Dictionary<int, long>>(new Dictionary<int, long>[N]);
                for(int j=0; j < N; j++)
                {
                    cache[j] = new Dictionary<int, long>();
                }
		
	//calcualte hits and misses for each one
                int hits = 0;
		int misses = 0;

                foreach (string item in ready)
                {
                    int tag_t = Convert.ToInt32(item.Substring(0, tag), 2);
                    int set_t = (set == 0) ? 0 : Convert.ToInt32(item.Substring(tag, set), 2);
                    if (isHit(cache, K, tag_t,set_t))  { hits++; }
                    else { misses++; }
                }

	//print to console
                Console.Write("L:" + L + ", N:" + N + ", K:" + K + ". " + "hits: " + hits + ", misses: " + misses + "\n");
            }
        }
    }
}
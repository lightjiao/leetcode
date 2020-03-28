/**
给定一个单词列表，我们将这个列表编码成一个索引字符串 S 与一个索引列表 A。

例如，如果这个列表是 ["time", "me", "bell"]，我们就可以将其表示为 S =
"time#bell#" 和 indexes = [0, 2, 5]。 对于每一个索引，我们可以通过从字符串
S 中索引的位置开始读取字符串，直到 "#" 结束，来恢复我们之前的单词列表。
那么成功对给定单词列表进行编码的最小字符串长度是多少呢？

示例：
输入: words = ["time", "me", "bell"]
输出: 10
说明: S = "time#bell#" ， indexes = [0, 2, 5] 。
 
提示：
1 <= words.length <= 2000
1 <= words[i].length <= 7
每个单词都是小写字母 。
 */

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do
                           // this in one cpp file
#include "../ListNode.cpp"
#include "../VV.cpp"
#include "../catch.hpp"

#include "limits.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class TrieNode
{
    // vector<TrieNode> children;
    TrieNode* children[26];

public:
    bool isKey;  // 标记改节点是否是一个关键字
    int  count;  // 记录该节点代表的单词个数 for 词频统计

    TrieNode()
    {
        for (int i = 0; i < 26; i++) {
            children[i] = NULL;
        }
        count = 0;
    }

    TrieNode* get(char c)
    {
        if (children[c - 'a'] == NULL) {
            children[c - 'a'] = new TrieNode();
            count++;
        }
        return children[c - 'a'];
    }
};

class Solution
{
public:
    /**
     * 后缀树
     */
    int minimumLengthEncoding(vector<string>& words)
    {
        TrieNode* trie = new TrieNode();

        unordered_map<TrieNode*, int> nodes;  // 记录单词长度统计结果?

        for (int i = 0; i < words.size(); i++) {
            string    word = words[i];
            TrieNode* cur  = trie;
            for (int j = word.size() - 1; j >= 0; j--) {
                cur = cur->get(word[j]);
            }
            nodes[cur] = i;
        }

        int result = 0;
        for (auto&& [node, idx] : nodes) {
            if (node->count == 0) {
                result += words[idx].size() + 1;
            }
        }

        return result;
    }
};

TEST_CASE("test")
{
    Solution s;

    vector<string> param;

    param = {"time", "me", "bell"};
    REQUIRE(s.minimumLengthEncoding(param) == 10);

    param = {"time", "time"};
    REQUIRE(s.minimumLengthEncoding(param) == 5);

    param = {"time", "im"};
    REQUIRE(s.minimumLengthEncoding(param) == 8);

    param = {"me", "time"};
    REQUIRE(s.minimumLengthEncoding(param) == 5);

    param = {"ojtnj",   "uuydcho", "dgsyp",   "dwxycpx", "dpmvc",   "dvfhmb",
             "flrxjjx", "fwhdhvn", "rgsakp",  "aiconf",  "nzacpk",  "sbxnaj",
             "shway",   "rgrmz",   "rysudo",  "bzkioce", "mqxkzvu", "wyebk",
             "tymoaz",  "mlmbg",   "djbmek",  "qfnme",   "khkiyae", "tjdaxry",
             "sqtcwz",  "ehnsai",  "jhncvrm", "cxkzgrx", "pummt",   "hzrpfcn",
             "lkyqit",  "phpqdxw", "vangm",   "wcjdgw",  "pxesvtn", "mnqory",
             "bdrzvh",  "brtzmo",  "chqgf",   "bipyxm",  "meoikg",  "ysyckk",
             "ojayeiq", "zrfbsb",  "yhuotea", "crfbhq",  "tllycn",  "qxnzihf",
             "avyawpz", "bwsjym",  "myjozc",  "lbdksm",  "mctlt",   "dszowuw",
             "syshm",   "xrvhhkn", "kgrcwfv", "dwlajlf", "yviuk",   "xegjj",
             "spiczl",  "vfvomi",  "mgcujy",  "dqmzb",   "isrisgt", "vdrtuah",
             "vsyth",   "eoclef",  "poccek",  "cgafrlu", "crbhpgk", "sromv",
             "xmvbca",  "gobra",   "ygvlq",   "pjvhe",   "tfweiso", "cskuohg",
             "eyalone", "pobkak",  "nzpxn",   "lbcrws",  "uhtfe",   "eorth",
             "showvu",  "hxsmb",   "jrggose", "izifkb",  "oqwyf",   "mozmzj",
             "ijwle",   "ggtqqqv", "geevzj",  "meota",   "ifsse",   "kdtofm",
             "swydhvf", "tzjhqap", "wqwwd",   "jlinnov", "lmxkgeg", "stbot",
             "xrsfn",   "etoyctk", "rygagm",  "vcnrf",   "zkdge",   "emqtscp",
             "newqcyy", "nnuus",   "exwsxbd", "zstvl",   "lbkko",   "kygkyqq",
             "oggji",   "xytbjo",  "mfbahk",  "ggoks",   "lmqewkl", "qexhyqe",
             "ogaogio", "nzvbav",  "mdole",   "qvyks",   "gkupfu",  "dgmpn",
             "ngrdrj",  "iitqvk",  "ipuiqb",  "ugxfea",  "ialkmv",  "hmgnx",
             "aoyoj",   "fvzhjil", "butrbp",  "dwhxnes", "etkdwg",  "cjkghz",
             "tovkq",   "mmxhv",   "jgcsn",   "hmictal", "zxmnek",  "pcoeg",
             "ntyqmlq", "hfubhtg", "ydjbv",   "xnwlqto", "hatgi",   "bsaczd",
             "pokwk",   "arxlula", "zjtqlk",  "ocfxup",  "nsnqjc",  "xdcsopi",
             "iqxyxp",  "xfmtpvm", "bqtgcf",  "wboycn",  "aoeda",   "uowqdgj",
             "rzzzx",   "liucs",   "ejzxz",   "qmlehsh", "igrbmon", "dpmkbon",
             "pmayh",   "nujdwdw", "awdgo",   "ijgkzk",  "inhee",   "jzdtv",
             "adhauh",  "grtmbp",  "qndbvw",  "zprrw",   "mpqieq",  "jzmzeuu",
             "fcvftqs", "qxzxqy",  "lidguzz", "eazwd",   "zjhfsz",  "zsnzefh",
             "mnckfg",  "zjgtq",   "ckyxlif", "fznfo",   "jegnof",  "lzwyzb",
             "ozivfio", "igkclsa", "bebzn",   "bitsggm", "lrnwin",  "hjnnzr",
             "idvoirn", "dgile",   "vfngh",   "xbmur",   "rqaftt",  "wjwwwxs",
             "btreou",  "gjsycg",  "pvsiylz", "ccxzgdf", "excrrrr", "fiesr",
             "jdioj",   "uzwsc",   "odrlcoy", "hcsit",   "ptwfprh", "sbqry",
             "kffvy",   "ejeawbp", "omvcc",   "iqgxqlt", "edsuu",   "xnbue",
             "qfbcx",   "fzlmbkl", "wrrcueb", "mmqispp", "nknilwd", "dewuhju",
             "hmdqlxy", "vjxgg",   "lkuexo",  "dzvfscm", "voulbs",  "uevoqgq",
             "kmhwu",   "oglzllg", "torhihn", "fhuqzc",  "mmcfhb",  "woyayma",
             "uznsvre", "mmxed",   "aoskwg",  "xrosbm",  "hpyrgh",  "tghwbwh",
             "hcwzn",   "iepeftj", "judij",   "kudbk",   "jonpv",   "lywck",
             "rxelz",   "bgifz",   "mehbxq",  "fmqnz",   "sqrmzj",  "iqqjzex",
             "qioliz",  "kjizbf",  "lgdcffc", "pfgmcr",  "trdabul", "vlqjdnc",
             "jjvbxe",  "fqlayw",  "ilbhtyq", "saawulw", "gxysrb",  "kighql",
             "eceapr",  "kztbcww", "jedkoy",  "dxpcaga", "ndacphe", "rcoit",
             "ywgcnxg", "klipfup", "bddws",   "jwyof",   "lrfwgo",  "bediwuf",
             "ujakh",   "ppima",   "xzhwvm",  "guzmsqt", "ffbliq",  "adjmynm",
             "akabzn",  "inmykju", "vlcjyv",  "orquepg", "tufrk",   "vqpjymm",
             "lvuab",   "qzxav",   "ekcmu",   "uqtuhie", "kfvtgf",  "nklwjo",
             "ujxlfpl", "zobfpq",  "eignijd", "ythctg",  "artllm",  "wodhh",
             "tzpwszq", "njdqegg", "hzrqib",  "zvoxtfd", "htboem",  "axjuix",
             "bvmvm",   "jbnum",   "bxdth",   "atejt",   "gqsqtnk", "fykrjbp",
             "ldyhonr", "wcuoj",   "upphc",   "agydg",   "cjmwk",   "rhxbqh",
             "tpgozdd", "qyqoy",   "zjqutw",  "qoohqny", "nsiacwz", "xupin",
             "criuvs",  "eswjeft", "pdmevn",  "zvogq",   "lrrvo",   "qhfqqpw",
             "ktudfg",  "ijvmi",   "neyjjdx", "rllpi",   "vllvaa",  "esebtu",
             "jyhcrh",  "otgmr",   "oudvyxj", "pmszy",   "opeed",   "gicni",
             "mnuzn",   "mjbfpod", "sqwgxu",  "dwniwz",  "wmbmmv",  "lyafuy",
             "zmvlz",   "kopxzuh", "urcbbiy", "guhco",   "nerjm",   "lpdxc",
             "hxmjzz",  "hynagc",  "iyxeczi", "bdfxmoz", "yybnpqd", "jvgnb",
             "oquqem",  "fmclmz",  "dmkhf",   "zxbjpp",  "qpxgcir", "iecvjm",
             "gtkne",   "lgtqrbc", "gilbn",   "mcxsg",   "ncwbhn",  "wkriiq",
             "zhsir",   "ptkkmw",  "jcbpkrm", "vbefo",   "vmbcd",   "vqffj",
             "fhqzjt",  "nryuh",   "vmclav",  "cjyggm",  "sanev",   "rrdocz",
             "zqdexbs", "jrxstt",  "pyhcesj", "aagghyr", "cyemjrb", "aliohf",
             "qaslg",   "pnyjzxz", "pehnvi",  "suhuw",   "twopabr", "sapqoc",
             "mckrh",   "nzlgrxt", "aqpobnu", "pirbjgb", "plzlj",   "raylxpu",
             "gyasfrh", "urjfxux", "xjbwau",  "iupknn",  "vhxnc",   "dnbjop",
             "vrxhwmd", "vjsmkh",  "rfmqids", "smaiwt",  "vkyfo",   "bjqyxc",
             "rbbbp",   "dlkzg",   "dwvdwu",  "prulzh",  "bavge",   "ehhrz",
             "xxjqk",   "pxopmp",  "okmkmb",  "slcznpp", "nvqlb",   "jalrk",
             "parwlcd", "anbxo",   "oqcxyzo", "fjhrdjh", "pgvnwfe", "yfjyvh",
             "quvszjm", "xyiig",   "xtncqv",  "svsix",   "jvpdnh",  "owuiv",
             "bsrugtt", "rmvggws", "lmdql",   "kvmvd",   "xrpmaw",  "ssnxyb",
             "oworq",   "rmmpuya", "rijpih",  "aelazka", "kncksqx", "yvtdiy",
             "epato",   "pbbamj",  "fejsw",   "zgsru",   "ekwrre",  "zqben",
             "vugxi",   "fvcsdp",  "rujcews", "asqxya",  "worjlsd", "xggakg",
             "kzfpot",  "haqon",   "ypqxzz",  "mmkzwt",  "bdhif",   "exzhv",
             "srnklzh", "hlrunb",  "dwfyke",  "fvgbtdm", "aeutp",   "czhefx",
             "tegfw",   "jkxpsb",  "gxkfkw",  "exvntd",  "gvuti",   "jdmly",
             "owaqhw",  "fopuxzv", "edrvil",  "biszwgv", "vgckzd",  "fqdxn",
             "qktdf",   "hpgwrk",  "gpxiips", "vxnlab",  "yylxz",   "hsuscch",
             "bhivaf",  "wzrwtc",  "ebplv",   "yzxykou", "mxlssom", "evghv",
             "hksleg",  "shybau",  "zeyqa",   "tljqka",  "axfkec",  "fatdj",
             "janlkcc", "sjorbra", "jplge",   "oazzot",  "qbgtncn", "ozlil",
             "stohadq", "rvpuwn",  "oqwpl",   "byftgi",  "ubuusl",  "fkogr",
             "bybdyhj", "vinyuzs", "ivsqvz",  "vmnae",   "gckxw",   "rozbe",
             "glvxwj",  "rcgicu",  "xmvbd",   "itycsry", "llmwrs",  "fuqth",
             "styrrwl", "wsseuln", "xwflcli", "muxgz",   "ypmbboh", "rpmvnep",
             "wjvvnv",  "arjnw",   "toauwc",  "ltjxqrl", "basffd",  "clxozwd",
             "glmrv",   "iejgfj",  "cvkoj",   "wotjf",   "mqucec",  "xalgemc",
             "hgimkh",  "golvfq",  "fuqpmak", "mhpcp",   "pxoibt",  "ledqa",
             "guzbyr",  "ztvbeka", "racdp",   "krsngra", "aaiknz",  "bhoobyc",
             "xibbe",   "yohepxk", "eclevs",  "ldliwcm", "qatvlk",  "eiypbw",
             "vxvtwa",  "nkdwsej", "ftmyvp",  "gpthye",  "gazwoi",  "zzgipon",
             "cithg",   "wpabujl", "jhezlnb", "vqqaxfg", "kvpbk",   "vggjemp",
             "owylv",   "lgwtfpg", "jjqvfm",  "xbhga",   "tulvfv",  "sefuo",
             "hbysv",   "ozopepd", "awyrifd", "pnudwx",  "vreje",   "zhpgw",
             "qygbf",   "tvbrvy",  "zzmcw",   "cznee",   "deuzxt",  "qfppjvi",
             "ilkps",   "ydwhg",   "krwkxzu", "mnsidg",  "rkxyyr",  "ajkqz",
             "xtmom",   "vqocor",  "fympcl",  "yyleyzy", "jjvzhrn", "kpmxvuz",
             "txoeqlx", "lhhmn",   "chzgpf",  "ncnjxle", "ihxrg",   "feqixq",
             "lkfhcar", "hfnsh",   "bifczy",  "umknat",  "yrhgkh",  "mgpcu",
             "qotukst", "yqlmfq",  "ttcdp",   "xnjjzm",  "cukbr",   "hjhjb",
             "iikfcsr", "nsqbnnz", "dauygf",  "cmydq",   "lfnhqnl", "ppqgs",
             "hscbfug", "ohzisud", "opspdkv", "aauxbop", "wpkhzo",  "sxbsgu",
             "tajrv",   "ololy",   "mxmus",   "vizvxv",  "osaqz",   "rxygkn",
             "mrzqlf",  "zrriyxb", "ufroe",   "bajozg",  "atpsu",   "uhgauzu",
             "tffdw",   "mdjulde", "rbrmy",   "jhkqvwl", "gzsultq", "nkbfi",
             "xtvwh",   "dryzcv",  "emaxuk",  "zucvutb", "jdduyk",  "bjdin",
             "loicuq",  "qhjjb",   "rgfjbq",  "mphnk",   "lxvceyx", "zeoxb",
             "fxhnxu",  "qpbipe",  "ophwp",   "wiioer",  "quchwj",  "pouxunw",
             "bloxgg",  "xbsma",   "dtwew",   "xstorn",  "qfrfkz",  "gxusbsn",
             "dhnxd",   "mhstbs",  "hekbtu",  "wvrrjw",  "yeiwd",   "patplsx",
             "qmyiyi",  "mowboj",  "iskyd",   "bqhjj",   "povppk",  "vthpwx",
             "uuydaw",  "rduxvez", "vmcww",   "ylruvph", "ymqosp",  "wzcvohg",
             "lhepwta", "bckhc",   "oiyyt",   "wqzfv",   "uduec",   "lkkbtzl",
             "prvpbo",  "jrwstii", "ijztoo",  "qwwth",   "vqzqiun", "krnjp",
             "zyanpiw", "ojhjhvg", "lohmb",   "thqtf",   "reptzv",  "zgkyq",
             "lhkvy",   "cmjwl",   "fmilgpw", "jrfawz",  "vrtzd",   "ezgfl",
             "plzng",   "zidzso",  "civavlg", "vtwopu",  "ljhckxo", "nuydt",
             "qembl",   "fiwrre",  "gfrgi",   "gzegiq",  "mltlqo",  "pcett",
             "snbsc",   "msibcqn", "beacrhz", "vsycjt",  "gjqji",   "smcegol",
             "zregkp",  "smcazoj", "dziqad",  "jpuwp",   "hnlztac", "vduitco",
             "wyencad", "bkdnnqo", "cabzyg",  "mgpcwr",  "fxgvkxt", "wlkcrdd",
             "bhmhsy",  "gqcctjc", "atafpt",  "vdzhmcg", "ighxj",   "gfqpale",
             "fohbrtj", "mfpsgt",  "tarjocf", "gyycb",   "qvqfryl", "jpwowwc",
             "jcgcg",   "gmrjze",  "nfptxq",  "hmjhxge", "ieelj",   "suvkgr",
             "nwjxe",   "tkepqm",  "extnpmq", "rxzdvf",  "relzaa",  "hfhgaq",
             "lmihlz",  "pacocq",  "dclxr",   "oknoem",  "pbpnnd",  "nleerfl",
             "tvytymc", "aamfnl",  "ufdnq",   "bxyzvyh", "vksvout", "lohxhf",
             "sskgn",   "aawbv",   "hrvhx",   "wvoqf",   "vxkvh",   "oqany",
             "bcmyd",   "epdddqn", "zrlej",   "bchaf",   "hmftii",  "mefcrz",
             "wbxvc",   "ewwnldf", "cqecxgh", "cnwvdmk", "vetrw",   "zmogwov",
             "lshlzpe", "lijay",   "tcdqg",   "xavqixd", "yjkhtsl", "myjvow",
             "cgthhd",  "taaii",   "iuuegk",  "lcypmle", "wesrit",  "tybco",
             "nhxysw",  "awkrj",   "jcmqa",   "porvo",   "nrypriu", "vznnevp",
             "hzklwi",  "vapuxh",  "wyfkn",   "albemu",  "ttfdbl",  "dbqrjv",
             "cxals",   "qzitwf",  "ysunur",  "llsefy",  "cghfzji", "jboaa",
             "emhlkw",  "khhmgha", "twlxgjz", "pyujor",  "ozcax",   "fetvovo",
             "mdhrrd",  "qdhdne",  "fiuvw",   "ebyxh",   "ldaothh", "vwyjf",
             "yjyljlu", "ivroqg",  "qvpeyec", "eemsdra", "wavgeqk", "bjejrqg",
             "mdjimoz", "fgopy",   "lgwodr",  "cunvszh", "wiver",   "ghmog",
             "jzgfyk",  "vxlbx",   "kvgbtn",  "cunorte", "mtesdc",  "zdzmqu",
             "pigik",   "smruadg", "czjxlt",  "kukgaok", "tsldpqq", "luomo",
             "ezbcvdc", "tfetwes", "uopzf",   "wsvezkw", "wrnlvbx", "bpqungd",
             "jqnnof",  "rqhiomi", "voulqb",  "ouspxn",  "chngpz",  "fbogfcv",
             "nqhunxo", "rydbke",  "ewduo",   "suqqwup", "oxzfxj",  "kuwfwm",
             "euiics",  "mvftoau", "vstfbm",  "vnmtoo",  "muicf",   "bjbskxb",
             "knbomlf", "enrbtfk", "hnaqe",   "vxzsr",   "gkqma",   "qygmn",
             "ztkybmb", "injggpk", "enqrgdk", "rkgoct",  "tgaiu",   "dnknoxk",
             "iwuou",   "oxanccl", "xestej",  "ekrqq",   "xbwhz",   "jkdvxfh",
             "oybaay",  "afyhci",  "papffjq", "bdppssw", "qwyvjx",  "xmnnosl",
             "kvqzjl",  "wcwii",   "ygfvt",   "tpabbht", "kjmaq",   "duschjz",
             "gguiof",  "wgfhve",  "joqmfjq", "smqfd",   "ynlovlz", "sgrzum",
             "bobmux",  "dcppi",   "isdjrwl", "lbevb",   "efqsirq", "hlgfql",
             "enmemlb", "dbmfk",   "ibfpzm",  "rtdnooq", "yicdq",   "xadul",
             "dxibxzi", "yyxnj",   "jhsdzxw", "thltbi",  "kwhreyi", "hrocoa",
             "fnaalbd", "vnwona",  "nnonm",   "naqaf",   "xgzzies", "uhruynk",
             "kgadfx",  "hyohzbd", "hnajx",   "yipzh",   "ezdxaet", "xbzppoz",
             "rwnewxz", "hlcbkmb", "znyhu",   "zsqtpkr", "gmyxr",   "rphyvo",
             "bgjuz",   "nulpv",   "eejfoso", "xmwcnes", "xxxxnpe", "jezkk",
             "idfsxrw", "qgzjtf",  "arpzpo",  "hxsanlt", "emvotcb", "sknzhvg",
             "icitca",  "ivhdln",  "sqilerz", "ndigw",   "bcsre",   "mibbep",
             "zsczom",  "cgghjbb", "fkylfgt", "bvzofs",  "mefsng",  "bispbza",
             "tsosgy",  "xopalrw", "wserf",   "jbmlz",   "xidxny",  "ffmpjos",
             "vddwxmd", "netnsg",  "kgevsp",  "pguuv",   "cwisp",   "slxiyb",
             "dmwaguc", "jobwusu", "uytcqrv", "hzhsy",   "zrlsdd",  "xhxah",
             "rxzij",   "zwdgy",   "ygmvkz",  "drkzbo",  "qpsal",   "tpxvl",
             "lfmfl",   "sayjvlh", "rdamym",  "ycuzd",   "zkycu",   "hdesec",
             "unequk",  "lpkdid",  "vorxls",  "admsdop", "rqnvkyg", "krnqqtb",
             "rxfms",   "xfthd",   "pxjbk",   "gpslrg",  "rwziwef", "usxgqvz",
             "baxxye",  "ocrkkrw", "lrlgsp",  "ceyctg",  "rniml",   "vavug",
             "jgircl",  "jrpnmsa", "rywvlfg", "prxnys",  "fkzmknn", "ooelc",
             "btvfs",   "yqepuvw", "tmmmb",   "qmpzexb", "zjckjvd", "aieytbb",
             "oafqq",   "szrcyh",  "czrxgae", "ifkte",   "hfgajox", "pwpnkqq",
             "yqphogn", "xuwthrd", "mpcmy",   "qitdoa",  "avlzfrh", "ywpip",
             "dgeki",   "fgbnx",   "tyofu",   "xziqzj",  "qxzvqz",  "vtsqk",
             "ipkld",   "yfhim",   "ebaegdc", "ubhrh",   "ldejv",   "mtflwy",
             "ocpyj",   "yopgqs",  "fkjxxd",  "njnnwr",  "nylkeb",  "taymdqv",
             "ekpznq",  "cbzobmg", "bucdds",  "qjozu",   "uvpghor", "obhnu",
             "ljkxbg",  "uqrxjtf", "xwbxiw",  "oxsmcg",  "spchdd",  "pcuitj",
             "faidq",   "tybmy",   "uygiyp",  "qloizj",  "cafgmy",  "smetd",
             "kwcwb",   "tdabxf",  "fpmrc",   "lfjujn",  "vvmvex",  "mnsgdc",
             "enjlgsw", "ohwcg",   "kxjdaup", "rotjarp", "aovdoq",  "oviwq",
             "qwaxs",   "bmazco",  "plcljsv", "yytjhl",  "vgwjm",   "drnue",
             "vqjgf",   "uqlsfy",  "bmqmfp",  "lkauwna", "ozmqce",  "heunaxr",
             "zaffbj",  "arbek",   "qjnllw",  "fdkhlz",  "wgmbwh",  "yceqag",
             "ltjjq",   "yurggfw", "puaafsl", "tjiqkyt", "yuzub",   "ytmrfq",
             "ommmu",   "ipknn",   "iubnuab", "dzthvc",  "zjbzpew", "dcooev",
             "pjydqcf", "zuojlzy", "zwjyfc",  "spmac",   "dfkbnz",  "fzriie",
             "asusog",  "hdodx",   "drjpo",   "ddyif",   "chabv",   "ebvkwrr",
             "burdjl",  "jjddi",   "dljzkye", "samyg",   "zwgxcq",  "xtratwo",
             "qfopz",   "xvlaw",   "laage",   "btdium",  "vzlnzt",  "kmvbzkq",
             "kctobsx", "kazbelu", "yxdwrk",  "eslvjc",  "nhsdmvs", "zuxqcc",
             "hqtxovn", "zrbdai",  "fgjxs",   "txecvio", "kjxlq",   "dkuxss",
             "mkbevn",  "pzmdqc",  "ihyia",   "atsub",   "twytus",  "nzooxj",
             "qwuoly",  "fdoigo",  "zukhlh",  "mugeaxt", "qqsfyls", "qqtql",
             "wrvphcx", "nzjfhx",  "uequtk",  "fxuto",   "qnast",   "nveys",
             "ltbrcth", "toctdib", "fbpnh",   "umxfgn",  "zvjuta",  "yeron",
             "qzvswqk", "gbctr",   "ryryz",   "zieknd",  "zcsna",   "jrhak",
             "zfxqsj",  "urlba",   "lbozqf",  "yfcjaa",  "hazgy",   "gmmfzyz",
             "zjvkyc",  "rvfdcf",  "daitab",  "hcxqgum", "qwakp",   "ltbsjwo",
             "pqqtygx", "upxcxao", "qylot",   "lmxqc",   "dwzcd",   "tjccm",
             "mqcpap",  "wgxqtr",  "ivycvxy", "wdykg",   "snvqka",  "jxtvtsb",
             "jnyowsq", "iwfuoig", "cuoixhu", "fzwalg",  "djhrar",  "sjmahk",
             "dyusf",   "wrxqvdi", "ftytlor", "jsjbv",   "vjbebg",  "agvsn",
             "vvmpgm",  "gsgjopk", "vbqvhy",  "afopf",   "zybfuz",  "aqsgc",
             "ytrjsvn", "wlhdfr",  "vdhvl",   "jrlvr",   "cscxwf",  "yhgbew",
             "wupbl",   "ssuhyvv", "bhcirzk", "oykwk",   "ijbto",   "qsnpgw",
             "otwzage", "ytqzh",   "rgwow",   "bvhgkwh", "fvawxie", "fllxw",
             "gfcqf",   "scoqb",   "qubrq",   "gdxjtp",  "ahrpck",  "awnlgi",
             "cmehsyp", "dwmytpy", "firyeq",  "oohwhr",  "caelk",   "mqemvs",
             "qflkzi",  "tfpibll", "ybhzd",   "ctsxri",  "yurocj",  "dnlnl",
             "ydmdva",  "xkaotl",  "xovax",   "ypynrqp", "kwfzw",   "fbgsmrc",
             "tutime",  "rcugul",  "cvewno",  "typhbpa", "wazew",   "flzfs",
             "wxxbza",  "ogjfkl",  "vjlebet", "imbubm",  "xinyncy", "dqmxfy",
             "buhagzh", "jjadpos", "gejyz",   "gxshqk",  "wkwrs",   "dqeriqo",
             "dmixr",   "bysjih",  "aoloq",   "ddwhsxs", "nteqv",   "cqagf",
             "ditsrn",  "wfxgl",   "jwjqb",   "rvkxj",   "rxapr",   "yrlkip",
             "npquasb", "nvezlr",  "gmhchcx", "lodfihi", "dheypxa", "plzjykh",
             "qopsthg", "zsnes",   "raongg",  "zrpnac",  "tzmtltj", "jsecdn",
             "rzudh",   "hkcyic",  "xsxmw",   "reeuwpn", "grkwrag", "gvzzbsq",
             "lrfta",   "aqyvbkj", "ytgfu",   "wcmvd",   "olnvfi",  "hhgmhb",
             "kojmepr", "wpohl",   "szhgg",   "hymiblu", "lkwjr",   "zulqpz",
             "sdcqjo",  "olgsgez", "lxkpqci", "yxcgn",   "gmvex",   "fskpppe",
             "utzto",   "axncvp",  "lcyahba", "ydeae",   "zvzar",   "ghfkkqv",
             "ryrpg",   "gucpbq",  "reofjz",  "cdnoo",   "dchhh",   "byiwd",
             "cqbhok",  "ksfnoa",  "xsmmlr",  "qyvdfqh", "dzshj",   "bpifnzh",
             "uxmoml",  "jdxvojf", "ihfll",   "vwesfof", "zynnpb",  "fwzra",
             "rxlgww",  "vkmjd",   "hcjgzt",  "mkapfl",  "ffjqlf",  "wulaebc",
             "gurramv", "tufkzai", "bxprqek", "nkohv",   "abgfwyl", "slslg",
             "wirsnh",  "pykvuh",  "fdrwk",   "gtmgsxe", "dxsaab",  "lqiryty",
             "aoezg",   "tzhugcg", "uoarf",   "dwhsv",   "rjiuoi",  "ycgcdnf",
             "rtfmwz",  "amkjc",   "woogtdi", "deprx",   "ucknu",   "womfm",
             "xdeev",   "qapxpuu", "ngulnk",  "fgtxyf",  "hnyabid", "cilmy",
             "wrsewtf", "luvtmo",  "wftuh",   "ifoeeqp", "dtfdhhl", "rwnburg",
             "fohkkul", "frqqi",   "gsrcyc",  "teuync",  "dvpvak",  "daqjki",
             "kksscp",  "somsde",  "tyfvck",  "ftfekl",  "ahncv",   "yvosm",
             "qgllvg",  "ylfwv",   "jenqns",  "lqovrnm", "iyger",   "nfvtsv",
             "bknxmqj", "pfzybdr", "hqjol",   "chlpk",   "etgrtqa", "msuxdx",
             "vnoatf",  "ypdzomn", "vsshmg",  "rfkipq",  "jvpbiz",  "vbskd",
             "edsoixj", "uowim",   "hqtsj",   "inbsxal", "ookrv",   "ipotdnk",
             "kmazqd",  "jpfghb",  "gvmnnpv", "juvwa",   "xtkvzw",  "ejqcl",
             "ebgcnt",  "ztuyu",   "dlzthw",  "zzipe",   "iaxwdxy", "htynwkc",
             "lefbq",   "pizfr",   "vttrsv",  "oagak",   "eqlrom",  "vttefg",
             "dsrmk",   "oekbe",   "cvugzk",  "diwvz",   "gxmfob",  "vjowzm",
             "mjpop",   "uznhz",   "kqvjwug", "wjqvxfg", "jbpwezu", "wsckdx",
             "slqfomn", "omuxk",   "zlgblso", "kvitoq",  "dmafq",   "djxmzk",
             "pjqfegq", "yjrttas", "siakcx",  "iutiqk",  "nwfdj",   "gbgtazk",
             "cpqtf",   "panmlr",  "aqubhsg", "iwdim",   "nqetym",  "mwazh",
             "thyhy",   "ydtxan",  "xfoin",   "lsosc",   "esznfa",  "xgdisi",
             "flvbzh",  "mpltx",   "iwjpsqp", "udfycf",  "rntmc",   "ltflwu",
             "wkgbaw",  "bcuzt",   "hejxuhb", "lguohe",  "klnhb",   "mjump",
             "avcwrol", "yrcqlc",  "ihxul",   "avajh",   "gtpauet", "iemzk",
             "rfdub",   "gqnbk",   "cfcmg",   "iobyh",   "iruuapf", "tyifwt",
             "sbdtp",   "mngcpmb", "oaqpolm", "mmimmh",  "gxknadi", "bmxhuu",
             "ulyoa",   "keidy",   "vsnfk",   "cnnnfty", "pkajm",   "ddgeecb",
             "prxidqd", "wmenvhd", "akjcqo",  "tnekfef", "ipvsi",   "pzjwq",
             "wmmct",   "erdjnuf", "vgeaqs",  "nlbdx",   "dpvbe",   "dgeqz",
             "aiguzh",  "akawppx", "tykrjcs", "gvavo",   "hkyle",   "yhedx",
             "xzqcg",   "gzdxt",   "csssbk",  "tmekrmv", "lfsgo",   "iizahz",
             "aszfd",   "aybqnsl", "vadwxsl", "ulmiii",  "xaxdugp", "sfnnsbg",
             "dkyruh",  "qhpqu",   "amesjd",  "evjuki",  "vtqjw",   "aoabp",
             "qnsuhe",  "bplbx",   "fdqok",   "ozkhgib", "cggwzys", "nbknjay",
             "ooambw",  "evmvegf", "htdlxik", "kahcume", "bojpn",   "bhipie",
             "hdyjslw", "pbkkq",   "qwszl",   "fgkbzsd", "hejdx",   "vmcfhgx",
             "puzlmmm", "meffil",  "boakbiz", "eczot",   "fvkkit",  "jebfx",
             "umvkjg",  "uikgs",   "rycgpf",  "rfmfgmy", "nveho",   "bgywqen",
             "gepfma",  "vquyq",   "wcercbw", "wbpjkxc", "rqloeda", "omclokx",
             "hvotwp",  "tvqfxxu", "qrtghk",  "hggme",   "arnmfnt", "cxprj",
             "rspdt",   "hlgfq",   "dmqel",   "pcerxk",  "ptqjc",   "wzreko",
             "kahks",   "xjnzo",   "xzzye",   "xbdeu",   "koiwkv",  "jlwkkjr",
             "xzdixoc", "xeedvrm", "mrtnhqi", "jaeann",  "mvubp",   "olklqf",
             "retbgcj", "qxxlhh",  "cqyyoy",  "ngwikg",  "qijte",   "sjzck",
             "zkmkx",   "ongtzf",  "tanow",   "smgntvq", "urfgt",   "xwcroa",
             "kadcpd",  "cxhgo",   "walku",   "kvvcsyt", "elwmuxk", "bfphtm",
             "vzeumuq", "sknvev",  "vbsnfd",  "grmbg",   "vjahwt",  "dmcbmn",
             "smubz",   "jobbfcv", "ujlkm",   "lcthh",   "bauuqdu", "kjgzgtq",
             "gicjz",   "nugbax",  "kbnjfiu", "sqfpein", "obbgfww", "ykggxjx",
             "irnmog",  "xniuv",   "rqiwycq", "hzlgyu",  "yjtrttv", "satym",
             "dgqhlkk", "rghal",   "tbekx",   "kkwmo",   "eahwhks", "bpvmbur",
             "sqtgkj",  "khboz",   "enefr",   "vkzqvt",  "wfruavu", "ninomu",
             "ypktaoa", "mlpmoit", "fxyhjfp", "fgnpp",   "txieja",  "dprnj",
             "bgyrp",   "zsqwqrw", "stqzki",  "kwiayb",  "ulbsn",   "aetje",
             "vwzbb",   "tedwyqs", "cymiruy", "jigpoqx", "ypuqsc",  "weletu",
             "gvibea",  "chhuldm", "baylv",   "wdhovo",  "imfqu",   "meodnsk",
             "jhlckqw", "jolyfh",  "jsfkrhr", "tnbfzvs", "egcfht",  "qnzmyr",
             "owtrqu",  "oqaqu",   "xftys",   "goxfftm", "sgbnp",   "bhfvaz",
             "gospa",   "jwzlvwk", "lqncoqd", "xxizglc", "bwffm",   "mhpggzr",
             "kdaoewx", "anviou",  "mqiij",   "wkskpn",  "enougdh", "vldnn",
             "gbfgz",   "ejmbh",   "qsdrvsx", "mrvbz",   "cqlufpf", "kbgjlu",
             "njgna",   "admrmk",  "pwwsc",   "gxkot",   "pdjwh",   "ejwxt",
             "bpaxufv", "iwjzs",   "xxfsg",   "vuhgh",   "srytgb",  "yesvlux",
             "tggnch",  "cgnbb",   "fbzbx",   "aomoqf",  "zkrvrjg", "ueaoz",
             "dppacnl", "ewovhxz", "kbvee",   "ixeeb",   "gwgoqm",  "hlwlxe",
             "fpmkrk",  "wzjsr",   "ispwe",   "garofu",  "jcmpec",  "tggeo",
             "yzdeo",   "axpmln",  "zhnlhck", "duyqcn",  "tpqwqi",  "jvmaj",
             "bisgoy",  "mpwmurb", "olqla",   "ecapwan", "kcpxn",   "xcapin",
             "ooctk",   "sgqql",   "vcyyjxf", "ejyom",   "jsgtha",  "logxnjg",
             "nypadhj", "dprmk",   "cqkuzb",  "gratv",   "tgkjgu",  "fttcafm",
             "tpryi",   "ubbhw",   "uwcuyn",  "zkgohs",  "snfesz",  "ifrex",
             "tkbfz",   "fvvkp",   "otjiq",   "lgomjjv", "ertracf", "bregu",
             "kkbizb",  "hyhvn",   "zjcnxfl", "mceskuj", "lmupdq",  "zdzqzgo",
             "yorppew", "fpwtjd",  "dxvyzt",  "bbnnu",   "pkycae",  "ucvapn",
             "dijmkb",  "nvwwpr",  "bufkw",   "zhono",   "vayxf",   "hlfwkev",
             "klkvkj",  "yzgpwg",  "lcbqr",   "tkkfi",   "pcgljx",  "bhduxu",
             "rgfipts", "hkjbrr",  "fobvy",   "wqmqhxo", "yjgvypg", "ehgoizl",
             "ipiibzh", "aqxbxtx", "lrtin",   "fyyuypr", "pyrocgm", "kwqbg",
             "ukccw",   "wgsbpvx", "pcoivrv", "okhxaba", "bbuaibf", "ccvfm",
             "phpst",   "yxtqiz",  "cdfbo",   "sijfljn", "gdlhn",   "bqmbced",
             "tiejf",   "aurqer",  "olmyd",   "prctay",  "lwflhi",  "bbehvta",
             "oxoda",   "lklyc",   "rzedhp",  "kairil",  "envan",   "wdcwfk",
             "xoroddb", "womrlr",  "ruxebe",  "jnpywrd", "wrifvz",  "zkewcd",
             "vllfrn",  "uvdvjh",  "bglpya",  "vzokkbw", "apaoqt",  "xpjizn",
             "xoajmd",  "xapjwc",  "jcknwg",  "bjpreep", "ffkua",   "ukcbah",
             "bugvkrf", "cbmmfs",  "cwaczhl", "nsqaj",   "sjeikg",  "fayqif",
             "slowoh",  "xjpvkpa", "ynunjle", "bqavt",   "nkpqudr", "neikvd",
             "yuqlzg",  "pdxbtrb", "cashlog", "iqiqy",   "smjmxv",  "zbtpbr",
             "zzamzcv", "jmakg",   "txfswc",  "pkaym",   "swlde",   "utann",
             "mqgpjne", "pslfvek", "nbiqhb",  "bzsianu", "wnxgbi",  "ahkeeiz",
             "dqdfjg",  "bptdg",   "pwita",   "uqyflq",  "txabjn",  "yznjmve",
             "mukcqqf", "cxonbf",  "ixuewjm", "pzlcat",  "eikeeo",  "scwsoa",
             "uaeyw",   "oeorff",  "gbqgd",   "qboqiv",  "hiulpb",  "dbbdm",
             "qvdxx",   "aypxbcn", "ykjwdbg", "pvfxn",   "shrqyz",  "zaxtu",
             "pfefgww", "jwifrw",  "zxuud",   "kpkwhlj", "lwptgd",  "zpdmvsw",
             "takeb",   "ynehl",   "kixtod",  "fyrgm",   "qirzmr",  "shyvec",
             "xjgzt",   "bwfvht",  "wyehh",   "renzc",   "nnibax",  "slhfng",
             "yjtecc",  "lghvbzf", "qroxvun", "mlsed",   "rrudho",  "cyffhh",
             "tjlxahp", "xmaepzk", "jvdzh",   "bbvegrw", "cebcz",   "odjpeam",
             "guerph",  "tgmphgo", "ohtkqq",  "jcxojz",  "haeheae", "erydxni",
             "hatjxx",  "kwmgkjw", "wmezvy",  "hsuuvfi", "ineek",   "grkxmhb",
             "alxkt",   "rmspxdg"};
    REQUIRE(s.minimumLengthEncoding(param) == 13956);
}

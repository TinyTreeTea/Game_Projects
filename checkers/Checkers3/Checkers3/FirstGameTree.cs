using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Checkers3
{
    class FirstGameTree
    {
        public sbyte[,] board;
        public List<SecondGameTree> list;
        public FirstGameTree()
        {
            list = new List<SecondGameTree>();
        }
        public FirstGameTree(sbyte[,] board)
        {
            this.board = board;
            list = new List<SecondGameTree>();
        }
    }
}

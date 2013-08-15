using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Checkers3
{
    class SecondGameTree
    {
        public sbyte[,] board;
        public List<GameTree> list;
        public int value;
        public SecondGameTree(sbyte[,] board)
        {
            this.board = board;
            list = new List<GameTree>();
        }
    }
}

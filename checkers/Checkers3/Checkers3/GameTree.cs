using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Checkers3
{
    class GameTree
    {
        public int value;
        public List<GameTree> list;
        public GameTree(int value)
        {
            this.value = value;
            list = new List<GameTree>();
        }
    }
}

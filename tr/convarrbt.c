


split (int i, int j)
{

    while (sti = qtop() && sti) {
        
        if (sti->l == sti->idx) {
            continue;
        }

        lm = (sti->l + sti->idx)/2;
        stlm->idx = lm;
        stlm->l = sti->l;
        stlm->r = sti->idx -1; 
        push(stlm);
       
        if (sti->idx+1 == sti->r) {
            continue;
        }

        rm = (sti->idx+1 + sti->r)/2;
        strm->idx = rm;
        strm->r = sti->r;
        stlm->i = sti->idx+1;
        qpush(strm);
    }
}

int 
main (int argc, char *argv[])
{

}

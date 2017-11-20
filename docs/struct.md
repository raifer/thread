# streamstate {
struct streamstate {
    int serial; // numéro du stream, utile pour le hash
    ogg_stream_state strstate; // automate de décodage du stream
    enum streamtype strtype;
    ogg_packet packet; // packet extrait du stream
    int nbpacket; // nb de packet complet extrait du stream
    int nbpacketoutsync; // nb de packet complet extrait du stream
    bool headersRead;
    struct theora_decode th_dec;
    struct vorbis_decode vo_dec;
    UT_hash_handle hh;
};

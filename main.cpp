struct personnage {
  int m_pdv;
  int m_force;
  int m_constitution;
  int m_agilite;

  personnage(int pdv, int force, int constitution, int agilite)
      : m_pdv(pdv), m_force(force), m_constitution(constitution),
        m_agilite(agilite) {}
};

int main() {}
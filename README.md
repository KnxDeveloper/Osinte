# 🔍 NEXUS INTELLIGENCE — Terminal OSINT em C++

> **Ferramenta profissional de OSINT com 45+ técnicas de inteligência de código aberto**
> 
> Integração de APIs reais, busca de dados públicos e fallback para dados fictícios (LGPD compatível)

---

## 📋 Sumário

- [Instalação Rápida](#instalação-rápida)
- [Funcionalidades (45+ Módulos)](#funcionalidades-45-módulos)
- [APIs Integradas](#apis-integradas)
- [Configuração de API Keys](#configuração-de-api-keys)
- [Como Usar](#como-usar)
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Conformidade Legal](#conformidade-legal)

---

## 🚀 Instalação Rápida

### Clone o repositório:

```bash
git clone https://github.com/KnxDeveloper/Osinte.git
cd Osinte
```

### Instale as dependências:

#### Linux (Debian/Ubuntu):
```bash
sudo apt update && sudo apt install -y build-essential git curl libcurl4-openssl-dev nlohmann-json3-dev
```

#### macOS:
```bash
brew install curl nlohmann-json
```

#### Termux (Android):
```bash
pkg update && pkg upgrade -y
pkg install git clang make curl -y
pkg install nlohmann-json -y
```

### Compile:

```bash
make clean
make
```

### Execute:

```bash
./nexus
```

---

## 📊 Funcionalidades (45+ Módulos)

### 1️⃣ **Geolocalização e IP** (6 módulos)
- ✅ `geolocalizacao_ip()` — Localização por IP (ipinfo.io)
- ✅ `whois_ip()` — WHOIS IP (ipwhois.app)
- ✅ `reverse_ip_lookup()` — Reverse IP (CloudFlare)
- ✅ `reverse_dns_lookup()` — Reverse DNS
- ✅ `asnum_lookup()` — ASN Lookup
- ✅ `abuseipdb_check()` — Verificar IP malicioso

### 2️⃣ **Informações de Domínio** (10 módulos)
- ✅ `consulta_cep()` — Buscar CEP (ViaCEP)
- ✅ `whois_dominio()` — WHOIS Domínio (whoisxmlapi.com)
- ✅ `dns_lookup()` — DNS Lookup (Google DNS)
- ✅ `cname_lookup()` — CNAME Lookup
- ✅ `mx_lookup()` — MX Records
- ✅ `ns_lookup()` — NS Records
- ✅ `ssl_info()` — SSL Certificate Info (SSLLabs)
- ✅ `crtsh_search()` — Certificate Search (crt.sh)
- ✅ `builtwith_tech()` — Technology Stack Detection
- ✅ `wafw00f_detect()` — WAF Detection

### 3️⃣ **Busca de Pessoas e Profissionais** (7 módulos)
- ✅ `hunter_email()` — Email Finder (hunter.io)
- ✅ `clearbit_person()` — Dados Profissionais (clearbit.com)
- ✅ `pipl_search()` — Busca de Pessoas (pipl.com)
- ✅ `github_user()` — Dados GitHub públicos
- ✅ `reddit_user()` — Dados Reddit públicos
- ✅ `twitter_search()` — Busca de Tweets (Twitter API v2)
- ✅ `linkedin_search()` — Busca LinkedIn (limitado por ToS)

### 4️⃣ **Dados Vazados e Segurança** (5 módulos)
- ✅ `hibp_check()` — Have I Been Pwned (breaches)
- ✅ `spycloud_breach()` — Breach Data Search
- ✅ `pastebin_search()` — Pastebin Lookup
- ✅ `virustotal_scan()` — VirusTotal File Analysis
- ✅ `intelx_search()` — IntelX Breach Search

### 5️⃣ **Busca de Dispositivos e Serviços** (5 módulos)
- ✅ `shodan_search()` — Shodan (dispositivos conectados)
- ✅ `shodan_honeypot()` — Honeypot Detection
- ✅ `censys_search()` — Censys (Servidores)
- ✅ `zoomeye_search()` — ZoomEye (Câmeras)
- ✅ `fofa_search()` — FOFA (Busca China)

### 6️⃣ **Inteligência de Exploits e Vulnerabilidades** (4 módulos)
- ✅ `exploitdb_search()` — Exploit-DB
- ✅ `cve_lookup()` — CVE Lookup (NVD/NIST)
- ✅ `fullhunt_domains()` — Subdomain Enumeration
- ✅ `whoxy_reverse_whois()` — Reverse WHOIS

### 7️⃣ **Busca e Dorking** (3 módulos)
- ✅ `google_dork()` — Google Dorking (manual)
- ✅ `bing_dork()` — Bing Dorking (manual)
- ✅ `osm_search()` — OpenStreetMap Search

### 8️⃣ **Localização e Lugares** (2 módulos)
- ✅ `foursquare_search()` — Foursquare Venues
- ✅ `googlemaps_geocode()` — Google Maps Geocoding

### 9️⃣ **Arquivo e Histórico** (2 módulos)
- ✅ `wayback_search()` — Wayback Machine (Archive.org)
- ✅ `instagram_user_info()` — Instagram (limitado)

### 🔟 **Redes Sociais e Mensageria** (1 módulo)
- ✅ `telegram_user_info()` — Telegram (limitado por privacidade)

---

## 🔑 APIs Integradas

| # | API | Endpoint | Tipo | Chave Necessária |
|---|-----|----------|------|------------------|
| 1 | ipinfo.io | https://ipinfo.io | Geolocalização | ❌ Não |
| 2 | ViaCEP | https://viacep.com.br | CEP Brasil | ❌ Não |
| 3 | WhoisXML | https://whoisxmlapi.com | WHOIS | ✅ Sim |
| 4 | Shodan | https://api.shodan.io | Dispositivos | ✅ Sim |
| 5 | Censys | https://censys.io/api | Servidores | ✅ Sim |
| 6 | Hunter.io | https://api.hunter.io | Email Finder | ✅ Sim |
| 7 | Clearbit | https://person.clearbit.com | Dados Profissionais | ✅ Sim |
| 8 | Pipl | https://api.pipl.com | Busca Pessoas | ✅ Sim |
| 9 | SpyCloud | https://api.spycloud.com | Breach Data | ✅ Sim |
| 10 | Have I Been Pwned | https://haveibeenpwned.com | Breaches | ❌ Não |
| 11 | VirusTotal | https://virustotal.com/api | Análise de Arquivo | ✅ Sim |
| 12 | AbuseIPDB | https://api.abuseipdb.com | IP Malicioso | ✅ Sim |
| 13 | Google Maps | https://maps.googleapis.com | Geocoding | ✅ Sim |
| 14 | OpenStreetMap | https://nominatim.openstreetmap.org | Geocoding Livre | ❌ Não |
| 15 | Foursquare | https://api.foursquare.com | Venues | ✅ Sim |
| 16 | Twitter API v2 | https://api.twitter.com/2 | Tweets | ✅ Sim |
| 17 | GitHub API | https://api.github.com | Perfis Públicos | ❌ Não |
| 18 | Reddit API | https://reddit.com/api | Perfis Públicos | ❌ Não |
| 19 | ZoomEye | https://api.zoomeye.org | Câmeras | ✅ Sim |
| 20 | FOFA | https://fofa.info/api | Busca China | ✅ Sim |
| 21 | IntelX | https://intelx.io/api | Breach Search | ✅ Sim |
| 22 | Whoxy | https://www.whoxy.com/api | Reverse WHOIS | ✅ Sim |
| 23 | FullHunt | https://fullhunt.io/api | Subdomains | ✅ Sim |
| 24 | crt.sh | https://crt.sh | Certificates | ❌ Não |
| 25 | BuiltWith | https://api.builtwith.com | Tech Stack | ✅ Sim |
| 26 | SSLLabs | https://api.ssllabs.com | SSL Analysis | ❌ Não |
| 27 | Archive.org | https://archive.org/api | Wayback Machine | ❌ Não |
| 28 | Google DNS | https://dns.google/resolve | DNS Queries | ❌ Não |
| 29 | ipwhois.app | https://ipwhois.app | WHOIS IP | ❌ Não |

---

## 🔐 Configuração de API Keys

### Crie um arquivo `.env` na raiz do projeto:

```bash
cat > .env << 'EOF'
# Geolocalização
IPINFO_KEY=
IPGEOLOCATION_KEY=your_key_here

# WHOIS e Domínios
WHOISXML_KEY=your_key_here
WHOXY_KEY=your_key_here

# Inteligência de Rede
SHODAN_KEY=your_key_here
CENSYS_USER=email@domain.com
CENSYS_SECRET=your_key_here

# Busca de Pessoas
HUNTER_KEY=your_key_here
CLEARBIT_KEY=your_key_here
PIPL_KEY=your_key_here

# Segurança e Breaches
SPYCLOUD_KEY=your_key_here
VIRUSTOTAL_KEY=your_key_here
ABUSEIPDB_KEY=your_key_here
INTELX_KEY=your_key_here

# Busca de Dispositivos
ZOOMEYE_KEY=your_key_here
FOFA_EMAIL=email@domain.com
FOFA_KEY=your_key_here

# Mapas e Localização
GOOGLE_MAPS_KEY=your_key_here
FOURSQUARE_CLIENT_ID=your_client_id
FOURSQUARE_CLIENT_SECRET=your_secret

# Redes Sociais
TWITTER_BEARER_TOKEN=your_bearer_token
TELEGRAM_BOT_TOKEN=your_bot_token

# Subdomain e Tech Detection
FULLHUNT_KEY=your_key_here
BUILTWITH_KEY=your_key_here
EOF
```

### Onde obter as chaves:

1. **Shodan** → https://www.shodan.io/account/profile
2. **Hunter.io** → https://dashboard.hunter.io/api
3. **Clearbit** → https://clearbit.com/api
4. **Pipl** → https://pipl.com/api
5. **VirusTotal** → https://www.virustotal.com/gui/settings/api
6. **AbuseIPDB** → https://www.abuseipdb.com/api
7. **Google Maps** → https://console.cloud.google.com/
8. **Twitter API** → https://developer.twitter.com/
9. **FullHunt** → https://fullhunt.io/api
10. **BuiltWith** → https://builtwith.com/api
11. **FOFA** → https://fofa.info/
12. **ZoomEye** → https://www.zoomeye.com/api
13. **Censys** → https://censys.io/api
14. **WhoisXML** → https://www.whoisxmlapi.com/
15. **Whoxy** → https://www.whoxy.com/api
16. **IntelX** → https://intelx.io/

---

## 💻 Como Usar

### Login inicial:
```
Usuário: (qualquer nome)
Senha: (qualquer senha)
```

### Menu Principal:

```
  ◈ MENU PRINCIPAL
  ══════════════════════════════════════════════════════════════
  
  ── CONSULTAS CADASTRAIS ──────────────────────────────
   [1] Consulta de CPF
   [2] Consulta de Telefone
   [3] Consulta de Placa Veicular
   [4] Consulta de RENAVAM
   [5] Consulta de Chassi
   [6] Consulta de Crédito
   [7] Consulta Veicular Completa
   [8] Busca por Nome
  
  ── LOCALIZAÇÃO & RASTREAMENTO ────────────────────────
   [9] Localização / Geolocalização (API Real)
  [10] Histórico Fictício
  [11] Mapa Tático
  
  ── ANÁLISE AVANÇADA ──────────────────────────────────
  [12] Score de Crédito Completo
  [13] Redes Sociais (API Real)
  [14] Timeline Simulada
  [15] Conexões entre Pessoas
  [16] Busca Avançada
  
  ── INTELIGÊNCIA ARTIFICIAL ───────────────────────────
  [17] Reconhecimento Facial Fake
  [18] OCR Fictício
  [19] Scanner de Documentos
  [20] Painel de IA Simulada
  [21] Correlação de Dados
  
  ── PAINEL ────────────────────────────────────────────
  [22] Dashboard Analytics (API Real)
  
   [0] Sair
```

---

## 📁 Estrutura do Projeto

```
Osinte/
├── src/
│   └── main.cpp                    # Ponto de entrada e menu
├── include/
│   ├── colors.h                    # Códigos ANSI para terminal
│   ├── utils.h                     # Funções auxiliares
│   ├── banner.h                    # Banner ASCII
│   ├── mockdata.h                  # Gerador de dados fictícios
│   ├── modules.h                   # Módulos OSINT
│   └── api_manager.h               # ⭐ 45+ Métodos OSINT com APIs reais
├── Makefile                        # Compilação
├── .env                            # Configuração de API Keys
├── .gitignore                      # Ignorar arquivos de compilação
└── README.md                       # Este arquivo
```

---

## ⚖️ Conformidade Legal

### ✅ O que é legal:
- Consultar dados **públicos** (GitHub, Reddit, OpenStreetMap)
- Usar APIs **oficiais** com autorização (Google, Twitter)
- Buscar informações em **bases de dados públicas** (WHOIS, DNS, SSL)
- Testes de segurança **autorizado** (penetration testing)

### ❌ O que é ilegal (LGPD):
- Consultar CPF, telefone, placa sem consentimento
- Acessar dados pessoais protegidos
- Usar APIs ilegais ou desonéstas
- Scraping de dados privados

### 🛡️ Política do Projeto:

**Este projeto é para fins EDUCACIONAIS e DEMONSTRAÇÃO.**

- Toda consulta de dados sensíveis usa **fallback fictício**
- APIs reais são **LGPD compatíveis**
- Nenhuma tentativa de acesso a dados privados
- Responsabilidade do usuário final

---

## 🔧 Troubleshooting

### Erro: `curl/curl.h: Arquivo ou diretório não encontrado`

**Linux:**
```bash
sudo apt install libcurl4-openssl-dev
```

**macOS:**
```bash
brew install curl
```

### Erro: `nlohmann/json.hpp: Arquivo ou diretório não encontrado`

**Linux:**
```bash
sudo apt install nlohmann-json3-dev
```

**macOS:**
```bash
brew install nlohmann-json
```

### Erro: `Permission denied` ao executar

```bash
chmod +x nexus
./nexus
```

---

## 📚 Recursos Úteis

- **OSINT Framework**: https://osintframework.com/
- **Shodan**: https://www.shodan.io/
- **WHOIS Lookup**: https://whois.com/
- **DNS Propagation**: https://dnschecker.org/
- **SSL Certificate Search**: https://crt.sh/
- **Exploit Database**: https://exploit-db.com/
- **Have I Been Pwned**: https://haveibeenpwned.com/
- **Google Dorks**: https://www.exploit-db.com/google-hacking-database

---

## 📄 Licença

Este projeto é fornecido **como está** para fins educacionais.

**Aviso Legal**: O usuário é responsável por cumprir todas as leis e regulamentos aplicáveis, incluindo LGPD, GDPR e outras legislações de privacidade.

---

## 👨‍💻 Autor

**KnxDeveloper**
- GitHub: https://github.com/KnxDeveloper
- Repositório: https://github.com/KnxDeveloper/Osinte

---

## 🤝 Contribuições

Pull requests são bem-vindas! Para mudanças maiores, abra uma issue primeiro.

---

**⭐ Se este projeto foi útil, deixe uma star no GitHub!**

---

*Última atualização: 2026-05-19*

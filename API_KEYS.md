# 🔑 Guia Completo de Configuração de API Keys

## 📋 Índice

1. [APIs Gratuitas (Sem Chave)](#apis-gratuitas-sem-chave)
2. [APIs Freemium (Com Limite Gratuito)](#apis-freemium-com-limite-gratuito)
3. [APIs Pagas (Chave Obrigatória)](#apis-pagas-chave-obrigatória)
4. [Tutorial Passo a Passo](#tutorial-passo-a-passo)
5. [Gerenciar Variáveis de Ambiente](#gerenciar-variáveis-de-ambiente)

---

## ✅ APIs Gratuitas (Sem Chave)

Estas APIs não requerem chave de API e podem ser usadas imediatamente:

### 1. ipinfo.io
- **Descrição**: Geolocalização por IP
- **Limite**: 50.000 requisições/mês
- **Link**: https://ipinfo.io/
- **Uso no código**:
  ```cpp
  auto result = APIManager::geolocalizacao_ip("8.8.8.8");
  ```

### 2. ViaCEP
- **Descrição**: Consulta CEP Brasil
- **Limite**: Sem limite
- **Link**: https://viacep.com.br/
- **Uso no código**:
  ```cpp
  auto result = APIManager::consulta_cep("01311-100");
  ```

### 3. OpenStreetMap (Nominatim)
- **Descrição**: Geocoding e busca de endereços
- **Limite**: 1 req/segundo (sem chave)
- **Link**: https://nominatim.openstreetmap.org/
- **Uso no código**:
  ```cpp
  auto result = APIManager::osm_search("São Paulo, Brasil");
  ```

### 4. GitHub API
- **Descrição**: Dados públicos de usuários
- **Limite**: 60 requisições/hora (sem autenticação)
- **Link**: https://api.github.com/
- **Uso no código**:
  ```cpp
  auto result = APIManager::github_user("torvalds");
  ```

### 5. Reddit API
- **Descrição**: Dados públicos de usuários
- **Limite**: 30 requisições/minuto
- **Link**: https://www.reddit.com/r/requestaccesstodata/
- **Uso no código**:
  ```cpp
  auto result = APIManager::reddit_user("username");
  ```

### 6. Have I Been Pwned (HIBP)
- **Descrição**: Verificar breaches de email
- **Limite**: Sem limite (respeitar User-Agent)
- **Link**: https://haveibeenpwned.com/API/v3
- **Uso no código**:
  ```cpp
  auto result = APIManager::hibp_check("email@example.com");
  ```

### 7. Google DNS
- **Descrição**: DNS Lookup, MX, NS records
- **Limite**: Sem limite (rate limiting)
- **Link**: https://dns.google/
- **Uso no código**:
  ```cpp
  auto result = APIManager::dns_lookup("example.com");
  ```

### 8. crt.sh
- **Descrição**: SSL Certificate Search
- **Limite**: Sem limite
- **Link**: https://crt.sh/
- **Uso no código**:
  ```cpp
  auto result = APIManager::crtsh_search("example.com");
  ```

### 9. SSLLabs
- **Descrição**: Análise de certificado SSL
- **Limite**: 2 requisições/10 segundos
- **Link**: https://www.ssllabs.com/
- **Uso no código**:
  ```cpp
  auto result = APIManager::ssl_info("example.com");
  ```

### 10. Archive.org (Wayback Machine)
- **Descrição**: Histórico de websites
- **Limite**: Sem limite
- **Link**: https://archive.org/api/
- **Uso no código**:
  ```cpp
  auto result = APIManager::wayback_search("example.com");
  ```

### 11. ipwhois.app
- **Descrição**: WHOIS IP
- **Limite**: 10.000/mês (grátis)
- **Link**: https://ipwhois.app/
- **Uso no código**:
  ```cpp
  auto result = APIManager::whois_ip("8.8.8.8");
  ```

---

## 🆓 APIs Freemium (Com Limite Gratuito)

Estas APIs oferecem plano gratuito com limitações:

### 1. Hunter.io
- **Descrição**: Email Finder (encontra emails de domínios)
- **Limite Grátis**: 50 requisições/mês
- **Link de Registro**: https://dashboard.hunter.io/auth/signup
- **Como obter chave**:
  1. Acesse https://dashboard.hunter.io/api
  2. Copie sua API Key
  3. Defina em `.env`: `HUNTER_KEY=your_key`
- **Uso no código**:
  ```cpp
  auto result = APIManager::hunter_email("example.com", "YOUR_API_KEY");
  ```

### 2. Clearbit
- **Descrição**: Dados profissionais de pessoas
- **Limite Grátis**: 100 requisições/mês
- **Link de Registro**: https://signup.clearbit.com/
- **Como obter chave**:
  1. Faça login em https://app.clearbit.com/
  2. Vá para Settings > API
  3. Copie seu API Key
  4. Defina em `.env`: `CLEARBIT_KEY=your_key`
- **Uso no código**:
  ```cpp
  auto result = APIManager::clearbit_person("email@example.com", "YOUR_API_KEY");
  ```

### 3. Pipl
- **Descrição**: Busca de pessoas na internet
- **Limite Grátis**: 100 requisições/mês
- **Link de Registro**: https://pipl.com/api/signup/
- **Como obter chave**:
  1. Crie conta em https://pipl.com/api/
  2. Vá para Dashboard
  3. Copie API Key
  4. Defina em `.env`: `PIPL_KEY=your_key`
- **Uso no código**:
  ```cpp
  auto result = APIManager::pipl_search("John Doe", "YOUR_API_KEY");
  ```

### 4. VirusTotal
- **Descrição**: Análise de malware em arquivos/URLs
- **Limite Grátis**: 4 requisições/minuto
- **Link de Registro**: https://www.virustotal.com/gui/signup
- **Como obter chave**:
  1. Faça login em https://www.virustotal.com/
  2. Vá para Settings > API
  3. Copie seu API Key
  4. Defina em `.env`: `VIRUSTOTAL_KEY=your_key`
- **Uso no código**:
  ```cpp
  auto result = APIManager::virustotal_scan("file_hash", "YOUR_API_KEY");
  ```

### 5. AbuseIPDB
- **Descrição**: Verificar IPs suspeitos
- **Limite Grátis**: 1.000 requisições/dia
- **Link de Registro**: https://www.abuseipdb.com/register
- **Como obter chave**:
  1. Faça login em https://www.abuseipdb.com/
  2. Vá para Account > API
  3. Copie sua API Key
  4. Defina em `.env`: `ABUSEIPDB_KEY=your_key`
- **Uso no código**:
  ```cpp
  auto result = APIManager::abuseipdb_check("192.168.1.1", "YOUR_API_KEY");
  ```

### 6. SSLLabs (Já Mencionado - Freemium)
- **Descrição**: Análise de certificado SSL
- **Limite**: 2 requisições/10 segundos
- **Sem chave necessária**

### 7. Google Dorking (Manual)
- **Descrição**: Busca avançada no Google
- **Sem API disponível** - use manualmente
- **Uso no código**:
  ```cpp
  auto result = APIManager::google_dork("site:example.com filetype:pdf");
  ```

### 8. Bing Dorking (Manual)
- **Descrição**: Busca avançada no Bing
- **Sem API disponível** - use manualmente
- **Uso no código**:
  ```cpp
  auto result = APIManager::bing_dork("site:example.com");
  ```

---

## 💰 APIs Pagas (Chave Obrigatória)

Estas APIs requerem plano pago. Oferecemos trial gratuito:

### 1. Shodan
- **Descrição**: Busca de dispositivos conectados
- **Preço**: $0-199/mês
- **Trial Grátis**: Não
- **Link**: https://www.shodan.io/
- **Como obter chave**:
  1. Crie conta em https://www.shodan.io/register
  2. Vá para Account > API
  3. Copie sua API Key
  4. Defina em `.env`: `SHODAN_KEY=your_key`
- **Uso no código**:
  ```cpp
  auto result = APIManager::shodan_search("apache", "YOUR_API_KEY");
  ```

### 2. Censys
- **Descrição**: Busca de servidores
- **Preço**: Freemium (50 requisições/mês)
- **Trial Grátis**: Sim
- **Link**: https://censys.io/
- **Como obter chave**:
  1. Crie conta em https://censys.io/register
  2. Vá para API > Create API Token
  3. Crie credenciais
  4. Defina em `.env`:
     ```
     CENSYS_USER=email@domain.com
     CENSYS_SECRET=your_secret
     ```
- **Uso no código**:
  ```cpp
  auto result = APIManager::censys_search("apache", "YOUR_API_KEY");
  ```

### 3. Whois XML API
- **Descrição**: WHOIS Domínio
- **Preço**: $19+/mês
- **Trial Grátis**: 100 requisições grátis
- **Link**: https://www.whoisxmlapi.com/
- **Como obter chave**:
  1. Crie conta em https://www.whoisxmlapi.com/account/signup
  2. Vá para API > Your Packages
  3. Copie API Key
  4. Defina em `.env`: `WHOISXML_KEY=your_key`
- **Uso no código**:
  ```cpp
  auto result = APIManager::whois_dominio("example.com", "YOUR_API_KEY");
  ```

### 4. SpyCloud
- **Descrição**: Breach data e credenciais vazadas
- **Preço**: Sob demanda
- **Link**: https://spycloud.com/
- **Como obter chave**:
  1. Solicite acesso em https://spycloud.com/request-access
  2. Após aprovação, acesse console
  3. Copie API Key
  4. Defina em `.env`: `SPYCLOUD_KEY=your_key`
- **Uso no código**:
  ```cpp
  auto result = APIManager::spycloud_breach("email@example.com", "YOUR_API_KEY");
  ```

### 5. Google Maps API
- **Descrição**: Geocoding, Maps
- **Preço**: $0.005-7 por requisição
- **Trial Grátis**: $200/mês
- **Link**: https://console.cloud.google.com/
- **Como obter chave**:
  1. Crie projeto em Google Cloud Console
  2. Ative "Maps JavaScript API"
  3. Crie API Key
  4. Defina em `.env`: `GOOGLE_MAPS_KEY=your_key`
- **Uso no código**:
  ```cpp
  auto result = APIManager::googlemaps_geocode("São Paulo, Brasil", "YOUR_API_KEY");
  ```

### 6. Twitter API v2
- **Descrição**: Busca de tweets, dados de usuários
- **Preço**: Grátis (Essential) - Pago (Pro+)
- **Link**: https://developer.twitter.com/
- **Como obter chave**:
  1. Crie aplicativo em https://developer.twitter.com/
  2. Gere Bearer Token
  3. Defina em `.env`: `TWITTER_BEARER_TOKEN=your_token`
- **Uso no código**:
  ```cpp
  auto result = APIManager::twitter_search("python", "YOUR_BEARER_TOKEN");
  ```

### 7. ZoomEye
- **Descrição**: Busca de câmeras e dispositivos
- **Preço**: Freemium
- **Link**: https://www.zoomeye.org/
- **Como obter chave**:
  1. Crie conta em https://www.zoomeye.org/user/register
  2. Vá para API
  3. Copie API Key ou gere JWT Token
  4. Defina em `.env`: `ZOOMEYE_KEY=your_key`
- **Uso no código**:
  ```cpp
  auto result = APIManager::zoomeye_search("webcam", "YOUR_API_KEY");
  ```

### 8. FOFA (Busca Chinesa)
- **Descrição**: Busca de dispositivos (principalmente China)
- **Preço**: Freemium
- **Link**: https://fofa.info/
- **Como obter chave**:
  1. Crie conta em https://fofa.info/
  2. Vá para User Profile > API
  3. Copie Email e API Key
  4. Defina em `.env`:
     ```
     FOFA_EMAIL=seu_email@domain.com
     FOFA_KEY=your_api_key
     ```
- **Uso no código**:
  ```cpp
  auto result = APIManager::fofa_search("query", "email", "API_KEY");
  ```

### 9. IntelX
- **Descrição**: Breach data, dark web search
- **Preço**: Freemium
- **Link**: https://intelx.io/
- **Como obter chave**:
  1. Crie conta em https://intelx.io/
  2. Copie API Key
  3. Defina em `.env`: `INTELX_KEY=your_key`
- **Uso no código**:
  ```cpp
  auto result = APIManager::intelx_search("email@example.com", "YOUR_API_KEY");
  ```

### 10. Whoxy (Reverse WHOIS)
- **Descrição**: Busca reversa de WHOIS
- **Preço**: $19.99+/mês
- **Link**: https://www.whoxy.com/
- **Como obter chave**:
  1. Crie conta em https://www.whoxy.com/
  2. Vá para API Keys
  3. Copie API Key
  4. Defina em `.env`: `WHOXY_KEY=your_key`
- **Uso no código**:
  ```cpp
  auto result = APIManager::whoxy_reverse_whois("email@domain.com", "YOUR_API_KEY");
  ```

### 11. FullHunt
- **Descrição**: Subdomain enumeration
- **Preço**: Freemium
- **Link**: https://fullhunt.io/
- **Como obter chave**:
  1. Crie conta em https://fullhunt.io/
  2. Vá para API
  3. Copie API Key
  4. Defina em `.env`: `FULLHUNT_KEY=your_key`
- **Uso no código**:
  ```cpp
  auto result = APIManager::fullhunt_domains("example.com", "YOUR_API_KEY");
  ```

### 12. BuiltWith
- **Descrição**: Detecção de tecnologia
- **Preço**: $99+/mês
- **Link**: https://builtwith.com/
- **Como obter chave**:
  1. Crie conta e adquira plano
  2. Copie API Key
  3. Defina em `.env`: `BUILTWITH_KEY=your_key`
- **Uso no código**:
  ```cpp
  auto result = APIManager::builtwith_tech("example.com", "YOUR_API_KEY");
  ```

### 13. Foursquare
- **Descrição**: Busca de venues e locais
- **Preço**: Freemium
- **Link**: https://foursquare.com/
- **Como obter chave**:
  1. Crie app em https://foursquare.com/
  2. Copie Client ID e Secret
  3. Defina em `.env`:
     ```
     FOURSQUARE_CLIENT_ID=your_id
     FOURSQUARE_CLIENT_SECRET=your_secret
     ```
- **Uso no código**:
  ```cpp
  auto result = APIManager::foursquare_search("café", -23.5505, -46.6333, "YOUR_SECRET");
  ```

---

## 🔧 Gerenciar Variáveis de Ambiente

### 1. Criar arquivo `.env`:

```bash
cat > .env << 'EOF'
# ============================================
# APIs Gratuitas (Não precisam de chave)
# ============================================
IPINFO_KEY=
OSM_KEY=

# ============================================
# APIs Freemium (Limite gratuito)
# ============================================
HUNTER_KEY=your_key_here
CLEARBIT_KEY=your_key_here
PIPL_KEY=your_key_here
VIRUSTOTAL_KEY=your_key_here
ABUSEIPDB_KEY=your_key_here

# ============================================
# APIs Pagas
# ============================================
SHODAN_KEY=your_key_here
CENSYS_USER=email@domain.com
CENSYS_SECRET=your_secret_here
WHOISXML_KEY=your_key_here
SPYCLOUD_KEY=your_key_here
GOOGLE_MAPS_KEY=your_key_here
TWITTER_BEARER_TOKEN=your_token_here
ZOOMEYE_KEY=your_key_here
FOFA_EMAIL=your_email@domain.com
FOFA_KEY=your_key_here
INTELX_KEY=your_key_here
WHOXY_KEY=your_key_here
FULLHUNT_KEY=your_key_here
BUILTWITH_KEY=your_key_here
FOURSQUARE_CLIENT_ID=your_client_id
FOURSQUARE_CLIENT_SECRET=your_secret
TELEGRAM_BOT_TOKEN=your_bot_token
EOF
```

### 2. Adicionar ao `.gitignore`:

```bash
echo ".env" >> .gitignore
echo "*.o" >> .gitignore
echo "nexus" >> .gitignore
```

### 3. Carregar variáveis em C++:

```cpp
#include <cstdlib>

// Exemplo de uso em api_manager.h
std::string api_key = std::getenv("SHODAN_KEY") ? std::getenv("SHODAN_KEY") : "";
if (api_key.empty()) {
    std::cerr << "[!] SHODAN_KEY não configurada em .env" << std::endl;
}
```

### 4. Testar configuração:

```bash
source .env  # Linux/macOS
echo $SHODAN_KEY  # Deve exibir sua chave
```

---

## 🎯 Checklist de Setup

- [ ] Clone o repositório
- [ ] Instale dependências (curl, nlohmann-json)
- [ ] Crie arquivo `.env`
- [ ] Registre-se em APIs gratuitas/freemium
- [ ] Copie API Keys para `.env`
- [ ] Execute `make clean && make`
- [ ] Execute `./nexus`
- [ ] Teste módulos de API

---

## 🚀 Próximos Passos

1. **Comece com APIs gratuitas**: ipinfo.io, ViaCEP, OpenStreetMap
2. **Teste APIs freemium**: Hunter, Clearbit, Pipl
3. **Upgrade para APIs pagas conforme necessário**
4. **Combine múltiplas APIs para análises completas**

---

**Última atualização**: 2026-05-19

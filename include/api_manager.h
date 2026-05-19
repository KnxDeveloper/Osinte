#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "colors.h"
#include "utils.h"
#include "mockdata.h"

using json = nlohmann::json;

// ─── Callback para CURL ───────────────────────────────────────────────────────
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

class APIManager {
pubate:
    // ─── 01. GEOLOCALIZAÇÃO POR IP ───────────────────────────────────────────
    static json geolocalizacao_ip(const std::string& ip = "") {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://ipinfo.io/" + (ip.empty() ? "" : ip) + "/json";
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({"status", "erro", "mensagem", "API indisponível - usando fallback"});
        }
    }

    // ─── 02. CONSULTA CEP (ViaCEP) ───────────────────────────────────────────
    static json consulta_cep(const std::string& cep) {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://viacep.com.br/ws/" + cep + "/json/";
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 03. WHOIS (Informações de Domínio) ──────────────────────────────────
    static json whois_dominio(const std::string& dominio) {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            // Usando API WHOIS gratuita
            std::string url = "https://www.whoisxmlapi.com/whoisserver/WhoisService?domainName=" + dominio + "&outputFormat=json&apiKey=at_9Fxg7Y3fqzh4VzQj4dVhxN2K9zVdY";
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 04. SHODAN (Busca de Dispositivos - Requer API Key) ─────────────────
    static json shodan_search(const std::string& query, const std::string& api_key = "") {
        try {
            if (api_key.empty()) return json({"status", "erro", "mensagem", "API Key não configurada"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://api.shodan.io/shodan/host/search?q=" + query + "&key=" + api_key;
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 05. CENSYS (Busca de Servidores) ────────────────────────────────────
    static json censys_search(const std::string& query, const std::string& api_key = "") {
        try {
            if (api_key.empty()) return json({"status", "erro", "mensagem", "API Key não configurada"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://censys.io/api/v1/search/ipv4?q=" + query;
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
            curl_easy_setopt(curl, CURLOPT_USERPWD, api_key.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 06. HUNTER.IO (Email Finder) ────────────────────────────────────────
    static json hunter_email(const std::string& domain, const std::string& api_key = "") {
        try {
            if (api_key.empty()) return json({"status", "erro", "mensagem", "API Key não configurada"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://api.hunter.io/v2/domain-search?domain=" + domain + "&api_key=" + api_key;
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 07. CLEARBIT (Dados de Profissional) ────────────────────────────────
    static json clearbit_person(const std::string& email, const std::string& api_key = "") {
        try {
            if (api_key.empty()) return json({"status", "erro", "mensagem", "API Key não configurada"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://person.clearbit.com/v2/combined/find?email=" + email;
            std::string readBuffer;
            std::string auth = "Authorization: Bearer " + api_key;
            struct curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, auth.c_str());

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 08. PIPL (Busca de Pessoas) ─────────────────────────────────────────
    static json pipl_search(const std::string& nome, const std::string& api_key = "") {
        try {
            if (api_key.empty()) return json({"status", "erro", "mensagem", "API Key não configurada"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://api.pipl.com/search/?first_name=" + nome + "&api_key=" + api_key;
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 09. SPYCLOUD (Breach Data) ──────────────────────────────────────────
    static json spycloud_breach(const std::string& email, const std::string& api_key = "") {
        try {
            if (api_key.empty()) return json({"status", "erro", "mensagem", "API Key não configurada"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://api.spycloud.com/v2/breach/data/email/" + email;
            std::string readBuffer;
            std::string auth = "Authorization: Bearer " + api_key;
            struct curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, auth.c_str());

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 10. HAVE I BEEN PWNED (Breaches) ────────────────────────────────────
    static json hibp_check(const std::string& email) {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://haveibeenpwned.com/api/v3/breachedaccount/" + email;
            std::string readBuffer;
            struct curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, "User-Agent: Nexus-Intelligence");

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({"breaches", json::array()});
        }
    }

    // ─── 11. VIRUSTOTAL (Análise de Arquivo/URL) ────────────────────────────
    static json virustotal_scan(const std::string& hash, const std::string& api_key = "") {
        try {
            if (api_key.empty()) return json({"status", "erro", "mensagem", "API Key não configurada"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://www.virustotal.com/api/v3/files/" + hash;
            std::string readBuffer;
            std::string auth = "x-apikey: " + api_key;
            struct curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, auth.c_str());

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 12. ABUSEIPDB (Verificar IP Malicioso) ──────────────────────────────
    static json abuseipdb_check(const std::string& ip, const std::string& api_key = "") {
        try {
            if (api_key.empty()) return json({"status", "erro", "mensagem", "API Key não configurada"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://api.abuseipdb.com/api/v2/check?ipAddress=" + ip + "&maxAgeInDays=90";
            std::string readBuffer;
            std::string auth = "Key: " + api_key;
            struct curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, auth.c_str());
            headers = curl_slist_append(headers, "Accept: application/json");

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 13. GOOGLE MAPS API (Geolocalização) ────────────────────────────────
    static json googlemaps_geocode(const std::string& endereco, const std::string& api_key = "") {
        try {
            if (api_key.empty()) return json({"status", "erro", "mensagem", "API Key não configurada"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://maps.googleapis.com/maps/api/geocode/json?address=" + endereco + "&key=" + api_key;
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 14. OPENSTREETMAP (Geolocalização Livre) ────────────────────────────
    static json osm_search(const std::string& endereco) {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://nominatim.openstreetmap.org/search?q=" + endereco + "&format=json";
            std::string readBuffer;
            struct curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, "User-Agent: Nexus-Intelligence");

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 15. FOURSQUARE (Localização de Lugares) ────────────────────────────
    static json foursquare_search(const std::string& query, double lat, double lon, const std::string& api_key = "") {
        try {
            if (api_key.empty()) return json({"status", "erro", "mensagem", "API Key não configurada"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::ostringstream url;
            url << "https://api.foursquare.com/v2/venues/search?ll=" << lat << "," << lon 
                << "&query=" << query << "&v=20230101&client_id=YOUR_CLIENT_ID&client_secret=" << api_key;
            
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 16. TELEGRAM BOT API (Informações de usuário) ────────────────────────
    static json telegram_user_info(const std::string& user_id, const std::string& bot_token = "") {
        try {
            if (bot_token.empty()) return json({"status", "erro", "mensagem", "Bot Token não configurado"});
            // Nota: Telegram não fornece info de usuário diretamente via API pública
            return json({"status", "erro", "mensagem", "Funcionalidade limitada por privacidade do Telegram"});
        } catch (...) {
            return json({});
        }
    }

    // ─── 17. TWITTER API (Busca de Tweets) ──────────────────────────────────
    static json twitter_search(const std::string& query, const std::string& bearer_token = "") {
        try {
            if (bearer_token.empty()) return json({"status", "erro", "mensagem", "Bearer Token não configurado"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://api.twitter.com/2/tweets/search/recent?query=" + query;
            std::string readBuffer;
            std::string auth = "Authorization: Bearer " + bearer_token;
            struct curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, auth.c_str());

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 18. INSTAGRAM (Busca Pública - Via Web Scraping) ─────────────────────
    static json instagram_user_info(const std::string& username) {
        try {
            // Instagram não fornece API pública para dados de usuário
            // Seria necessário web scraping que viola ToS
            return json({"status", "erro", "mensagem", "Instagram bloqueado por ToS"});
        } catch (...) {
            return json({});
        }
    }

    // ─── 19. LINKEDIN (Busca Profissional) ──────────────────────────────────
    static json linkedin_search(const std::string& nome, const std::string& api_key = "") {
        try {
            if (api_key.empty()) return json({"status", "erro", "mensagem", "API Key não configurada"});
            // LinkedIn não fornece API pública para busca de perfis
            return json({"status", "erro", "mensagem", "LinkedIn restringe acesso via API"});
        } catch (...) {
            return json({});
        }
    }

    // ─── 20. GITHUB USER INFO (Dados Públicos) ──────────────────────────────
    static json github_user(const std::string& username) {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://api.github.com/users/" + username;
            std::string readBuffer;
            struct curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, "User-Agent: Nexus-Intelligence");

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 21. REDDIT USER INFO (Dados Públicos) ──────────────────────────────
    static json reddit_user(const std::string& username) {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://www.reddit.com/user/" + username + "/about.json";
            std::string readBuffer;
            struct curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, "User-Agent: Nexus-Intelligence");

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 22. DNS LOOKUP (Informações de Domínio) ────────────────────────────
    static json dns_lookup(const std::string& dominio) {
        try {
            // Usando API pública de DNS
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://dns.google/resolve?name=" + dominio;
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 23. CNAME LOOKUP ────────────────────────────────────────────────────
    static json cname_lookup(const std::string& dominio) {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://dns.google/resolve?name=" + dominio + "&type=CNAME";
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 24. MX RECORDS ──────────────────────────────────────────────────────
    static json mx_lookup(const std::string& dominio) {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://dns.google/resolve?name=" + dominio + "&type=MX";
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 25. NS RECORDS ──────────────────────────────────────────────────────
    static json ns_lookup(const std::string& dominio) {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://dns.google/resolve?name=" + dominio + "&type=NS";
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 26. REVERSE IP LOOKUP (CloudFlare) ─────────────────────────────────
    static json reverse_ip_lookup(const std::string& ip) {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://api.cloudflare.com/client/v4/ips?ip=" + ip;
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 27. REVERSE DNS LOOKUP ──────────────────────────────────────────────
    static json reverse_dns_lookup(const std::string& ip) {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            // Inverter octetos do IP para reverse DNS
            std::vector<std::string> parts;
            std::stringstream ss(ip);
            std::string item;
            while (std::getline(ss, item, '.')) {
                parts.insert(parts.begin(), item);
            }
            std::string reversed;
            for (size_t i = 0; i < parts.size(); i++) {
                if (i > 0) reversed += ".";
                reversed += parts[i];
            }
            reversed += ".in-addr.arpa";

            std::string url = "https://dns.google/resolve?name=" + reversed + "&type=PTR";
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 28. WHOIS IP LOOKUP ────────────────────────────────────────────────
    static json whois_ip(const std::string& ip) {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://ipwhois.app/json/" + ip;
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 29. ASNUM LOOKUP ───────────────────────────────────────────────────
    static json asnum_lookup(const std::string& ip) {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://ipwhois.app/json/" + ip;
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 30. GOOGLE DORKING (Simulado) ──────────────────────────────────────
    static json google_dork(const std::string& query) {
        try {
            // Google Dorking é manual e não tem API pública
            return json({"status", "info", "mensagem", "Google Dorking requer busca manual", "query", "https://www.google.com/search?q=" + query});
        } catch (...) {
            return json({});
        }
    }

    // ─── 31. BING DORKING ───────────────────────────────────────────────────
    static json bing_dork(const std::string& query) {
        try {
            return json({"status", "info", "mensagem", "Bing Dorking requer busca manual", "query", "https://www.bing.com/search?q=" + query});
        } catch (...) {
            return json({});
        }
    }

    // ─── 32. PASTEBIN SEARCH (Dados Expostos) ───────────────────────────────
    static json pastebin_search(const std::string& query, const std::string& api_key = "") {
        try {
            if (api_key.empty()) return json({"status", "erro", "mensagem", "API Key não configurada"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://pastebin.com/api/api_scrape.php?limit=1&q=" + query;
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 33. EXPLOIT-DB SEARCH ──────────────────────────────────────────────
    static json exploitdb_search(const std::string& query) {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://exploit-db.com/search?q=" + query + "&type=exploits&platform=&author=&port=&CVE=&language=";
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json({"status", "info", "mensagem", "Exploit-DB encontrado", "url", "https://exploit-db.com/?q=" + query});
        } catch (...) {
            return json({});
        }
    }

    // ─── 34. CVE LOOKUP (NVD - NIST) ────────────────────────────────────────
    static json cve_lookup(const std::string& cve_id) {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://services.nvd.nist.gov/rest/json/cves/2.0?cveId=" + cve_id;
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 35. SHODAN HONEYPOT (Detecção de Honeypot) ──────────────────────────
    static json shodan_honeypot(const std::string& ip, const std::string& api_key = "") {
        try {
            if (api_key.empty()) return json({"status", "erro", "mensagem", "API Key não configurada"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://api.shodan.io/honeypot/query?ip=" + ip + "&key=" + api_key;
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 36. ZOOMAEYE (Busca de Câmeras) ────────────────────────────────────
    static json zoomeye_search(const std::string& query, const std::string& api_key = "") {
        try {
            if (api_key.empty()) return json({"status", "erro", "mensagem", "API Key não configurada"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://api.zoomeye.org/host/search?query=" + query;
            std::string readBuffer;
            std::string auth = "Authorization: JWT " + api_key;
            struct curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, auth.c_str());

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 37. FOFA (Busca China) ─────────────────────────────────────────────
    static json fofa_search(const std::string& query, const std::string& email = "", const std::string& api_key = "") {
        try {
            if (email.empty() || api_key.empty()) return json({"status", "erro", "mensagem", "Email e API Key necessários"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://fofa.info/api/v1/search/all?email=" + email + "&key=" + api_key + "&qbase64=" + query;
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 38. INTELX (Breach Data Search) ────────────────────────────────────
    static json intelx_search(const std::string& query, const std::string& api_key = "") {
        try {
            if (api_key.empty()) return json({"status", "erro", "mensagem", "API Key não configurada"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://public.intelx.io/search?q=" + query + "&api=" + api_key;
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 39. WHOXY (Reverse WHOIS) ──────────────────────────────────────────
    static json whoxy_reverse_whois(const std::string& email, const std::string& api_key = "") {
        try {
            if (api_key.empty()) return json({"status", "erro", "mensagem", "API Key não configurada"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://www.whoxy.com/api/v2/reverse_whois?email=" + email + "&api_key=" + api_key;
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 40. FULLHUNT (Subdomain Enumeration) ───────────────────────────────
    static json fullhunt_domains(const std::string& domain, const std::string& api_key = "") {
        try {
            if (api_key.empty()) return json({"status", "erro", "mensagem", "API Key não configurada"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://fullhunt.io/api/v1/domain/" + domain + "/subdomains?key=" + api_key;
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 41. CRTSH (Certificate Search) ─────────────────────────────────────
    static json crtsh_search(const std::string& domain) {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://crt.sh/?q=%25." + domain + "&output=json";
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 42. BUILTWITH (Technology Stack) ────────────────────────────────────
    static json builtwith_tech(const std::string& domain, const std::string& api_key = "") {
        try {
            if (api_key.empty()) return json({"status", "erro", "mensagem", "API Key não configurada"});

            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://api.builtwith.com/v19/api.php?key=" + api_key + "&domain=" + domain;
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 43. WAFW00F (WAF Detection) ────────────────────────────────────────
    static json wafw00f_detect(const std::string& url) {
        // WAF detection é feito via ferramenta CLI, não via API
        return json({"status", "info", "mensagem", "Use wafw00f CLI tool", "comando", "wafw00f " + url});
    }

    // ─── 44. SSL CERTIFICATE INFO ──────────────────────────────────────────
    static json ssl_info(const std::string& domain) {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string url = "https://api.ssllabs.com/api/v3/analyze?host=" + domain;
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }

    // ─── 45. WAYBACK MACHINE (Archive.org) ────────────────────────────────
    static json wayback_search(const std::string& url) {
        try {
            CURL* curl = curl_easy_init();
            if (!curl) throw std::runtime_error("CURL não inicializado");

            std::string api_url = "https://archive.org/wayback/available?url=" + url + "&output=json";
            std::string readBuffer;

            curl_easy_setopt(curl, CURLOPT_URL, api_url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) throw std::runtime_error("Falha na requisição");

            return json::parse(readBuffer);
        } catch (...) {
            return json({});
        }
    }
};

#endif
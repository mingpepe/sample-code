import m3u8
import requests
import sys

headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/78.0.3904.97 Safari/537.36',
}

def main():
    if len(sys.argv) != 2:
        print('[Usage] python main.py url_to_m3u8')
        return

    m3u8_obj = m3u8.load(sys.argv[1])
    with open('output.mp4', 'wb') as out:
        for seg in m3u8_obj.segments:
            uri = f'{m3u8_obj.base_uri}/{seg.uri}'
            response = requests.get(uri, headers=headers, timeout=10)
            if response.status_code == 200:
                out.write(response.content)

if __name__ == '__main__':
    main()